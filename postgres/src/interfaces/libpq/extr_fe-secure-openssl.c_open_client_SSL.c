#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sebuf ;
struct TYPE_5__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/ * peer; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  PostgresPollingStatusType ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 unsigned long ERR_get_error () ; 
 int /*<<< orphan*/  PGRES_POLLING_FAILED ; 
 int /*<<< orphan*/  PGRES_POLLING_OK ; 
 int /*<<< orphan*/  PGRES_POLLING_READING ; 
 int /*<<< orphan*/  PGRES_POLLING_WRITING ; 
 int PG_STRERROR_R_BUFLEN ; 
 int /*<<< orphan*/  SOCK_ERRNO ; 
 char* SOCK_STRERROR (int /*<<< orphan*/ ,char*,int) ; 
#define  SSL_ERROR_SSL 131 
#define  SSL_ERROR_SYSCALL 130 
#define  SSL_ERROR_WANT_READ 129 
#define  SSL_ERROR_WANT_WRITE 128 
 int SSL_connect (int /*<<< orphan*/ ) ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLerrfree (char*) ; 
 char* SSLerrmessage (unsigned long) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pgtls_close (TYPE_1__*) ; 
 int /*<<< orphan*/  pq_verify_peer_name_matches_certificate (TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static PostgresPollingStatusType
open_client_SSL(PGconn *conn)
{
	int			r;

	ERR_clear_error();
	r = SSL_connect(conn->ssl);
	if (r <= 0)
	{
		int			err = SSL_get_error(conn->ssl, r);
		unsigned long ecode;

		ecode = ERR_get_error();
		switch (err)
		{
			case SSL_ERROR_WANT_READ:
				return PGRES_POLLING_READING;

			case SSL_ERROR_WANT_WRITE:
				return PGRES_POLLING_WRITING;

			case SSL_ERROR_SYSCALL:
				{
					char		sebuf[PG_STRERROR_R_BUFLEN];

					if (r == -1)
						printfPQExpBuffer(&conn->errorMessage,
										  libpq_gettext("SSL SYSCALL error: %s\n"),
										  SOCK_STRERROR(SOCK_ERRNO, sebuf, sizeof(sebuf)));
					else
						printfPQExpBuffer(&conn->errorMessage,
										  libpq_gettext("SSL SYSCALL error: EOF detected\n"));
					pgtls_close(conn);
					return PGRES_POLLING_FAILED;
				}
			case SSL_ERROR_SSL:
				{
					char	   *err = SSLerrmessage(ecode);

					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("SSL error: %s\n"),
									  err);
					SSLerrfree(err);
					pgtls_close(conn);
					return PGRES_POLLING_FAILED;
				}

			default:
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("unrecognized SSL error code: %d\n"),
								  err);
				pgtls_close(conn);
				return PGRES_POLLING_FAILED;
		}
	}

	/*
	 * We already checked the server certificate in initialize_SSL() using
	 * SSL_CTX_set_verify(), if root.crt exists.
	 */

	/* get server certificate */
	conn->peer = SSL_get_peer_certificate(conn->ssl);
	if (conn->peer == NULL)
	{
		char	   *err;

		err = SSLerrmessage(ERR_get_error());

		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("certificate could not be obtained: %s\n"),
						  err);
		SSLerrfree(err);
		pgtls_close(conn);
		return PGRES_POLLING_FAILED;
	}

	if (!pq_verify_peer_name_matches_certificate(conn))
	{
		pgtls_close(conn);
		return PGRES_POLLING_FAILED;
	}

	/* SSL handshake is complete */
	return PGRES_POLLING_OK;
}