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
struct TYPE_3__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
#define  EAGAIN 131 
#define  ECONNRESET 130 
#define  EINTR 129 
#define  EWOULDBLOCK 128 
 int PG_STRERROR_R_BUFLEN ; 
 int SOCK_ERRNO ; 
 int /*<<< orphan*/  SOCK_ERRNO_SET (int) ; 
 int /*<<< orphan*/  SOCK_STRERROR (int,char*,int) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

ssize_t
pqsecure_raw_read(PGconn *conn, void *ptr, size_t len)
{
	ssize_t		n;
	int			result_errno = 0;
	char		sebuf[PG_STRERROR_R_BUFLEN];

	n = recv(conn->sock, ptr, len, 0);

	if (n < 0)
	{
		result_errno = SOCK_ERRNO;

		/* Set error message if appropriate */
		switch (result_errno)
		{
#ifdef EAGAIN
			case EAGAIN:
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
			case EWOULDBLOCK:
#endif
			case EINTR:
				/* no error message, caller is expected to retry */
				break;

#ifdef ECONNRESET
			case ECONNRESET:
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext(
												"server closed the connection unexpectedly\n"
												"\tThis probably means the server terminated abnormally\n"
												"\tbefore or while processing the request.\n"));
				break;
#endif

			default:
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("could not receive data from server: %s\n"),
								  SOCK_STRERROR(result_errno,
												sebuf, sizeof(sebuf)));
				break;
		}
	}

	/* ensure we return the intended errno to caller */
	SOCK_ERRNO_SET(result_errno);

	return n;
}