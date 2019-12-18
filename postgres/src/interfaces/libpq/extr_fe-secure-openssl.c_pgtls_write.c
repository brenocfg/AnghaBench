#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  sebuf ;
struct TYPE_3__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int ECONNRESET ; 
 int EPIPE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 unsigned long ERR_get_error () ; 
 int PG_STRERROR_R_BUFLEN ; 
 int SOCK_ERRNO ; 
 int /*<<< orphan*/  SOCK_ERRNO_SET (int) ; 
 int SOCK_STRERROR (int,char*,int) ; 
#define  SSL_ERROR_NONE 133 
#define  SSL_ERROR_SSL 132 
#define  SSL_ERROR_SYSCALL 131 
#define  SSL_ERROR_WANT_READ 130 
#define  SSL_ERROR_WANT_WRITE 129 
#define  SSL_ERROR_ZERO_RETURN 128 
 int SSL_get_error (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SSL_write (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  SSLerrfree (char*) ; 
 char* SSLerrmessage (unsigned long) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,char*,...) ; 

ssize_t
pgtls_write(PGconn *conn, const void *ptr, size_t len)
{
	ssize_t		n;
	int			result_errno = 0;
	char		sebuf[PG_STRERROR_R_BUFLEN];
	int			err;
	unsigned long ecode;

	SOCK_ERRNO_SET(0);
	ERR_clear_error();
	n = SSL_write(conn->ssl, ptr, len);
	err = SSL_get_error(conn->ssl, n);
	ecode = (err != SSL_ERROR_NONE || n < 0) ? ERR_get_error() : 0;
	switch (err)
	{
		case SSL_ERROR_NONE:
			if (n < 0)
			{
				/* Not supposed to happen, so we don't translate the msg */
				printfPQExpBuffer(&conn->errorMessage,
								  "SSL_write failed but did not provide error information\n");
				/* assume the connection is broken */
				result_errno = ECONNRESET;
			}
			break;
		case SSL_ERROR_WANT_READ:

			/*
			 * Returning 0 here causes caller to wait for write-ready, which
			 * is not really the right thing, but it's the best we can do.
			 */
			n = 0;
			break;
		case SSL_ERROR_WANT_WRITE:
			n = 0;
			break;
		case SSL_ERROR_SYSCALL:
			if (n < 0)
			{
				result_errno = SOCK_ERRNO;
				if (result_errno == EPIPE || result_errno == ECONNRESET)
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext(
													"server closed the connection unexpectedly\n"
													"\tThis probably means the server terminated abnormally\n"
													"\tbefore or while processing the request.\n"));
				else
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("SSL SYSCALL error: %s\n"),
									  SOCK_STRERROR(result_errno,
													sebuf, sizeof(sebuf)));
			}
			else
			{
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("SSL SYSCALL error: EOF detected\n"));
				/* assume the connection is broken */
				result_errno = ECONNRESET;
				n = -1;
			}
			break;
		case SSL_ERROR_SSL:
			{
				char	   *errm = SSLerrmessage(ecode);

				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("SSL error: %s\n"), errm);
				SSLerrfree(errm);
				/* assume the connection is broken */
				result_errno = ECONNRESET;
				n = -1;
				break;
			}
		case SSL_ERROR_ZERO_RETURN:

			/*
			 * Per OpenSSL documentation, this error code is only returned for
			 * a clean connection closure, so we should not report it as a
			 * server crash.
			 */
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("SSL connection has been closed unexpectedly\n"));
			result_errno = ECONNRESET;
			n = -1;
			break;
		default:
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("unrecognized SSL error code: %d\n"),
							  err);
			/* assume the connection is broken */
			result_errno = ECONNRESET;
			n = -1;
			break;
	}

	/* ensure we return the intended errno to caller */
	SOCK_ERRNO_SET(result_errno);

	return n;
}