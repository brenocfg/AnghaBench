#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  len; } ;
struct TYPE_15__ {int password_needed; size_t whichhost; char* pgpass; TYPE_3__ errorMessage; int /*<<< orphan*/ * sasl_state; TYPE_1__* connhost; int /*<<< orphan*/  usesspi; int /*<<< orphan*/  gsslib; } ;
struct TYPE_14__ {char* password; } ;
typedef  TYPE_2__ PGconn ;
typedef  int AuthRequest ;

/* Variables and functions */
#define  AUTH_REQ_CRYPT 140 
#define  AUTH_REQ_GSS 139 
#define  AUTH_REQ_GSS_CONT 138 
#define  AUTH_REQ_KRB4 137 
#define  AUTH_REQ_KRB5 136 
#define  AUTH_REQ_MD5 135 
#define  AUTH_REQ_OK 134 
#define  AUTH_REQ_PASSWORD 133 
#define  AUTH_REQ_SASL 132 
#define  AUTH_REQ_SASL_CONT 131 
#define  AUTH_REQ_SASL_FIN 130 
#define  AUTH_REQ_SCM_CREDS 129 
#define  AUTH_REQ_SSPI 128 
 int /*<<< orphan*/  PQnoPasswordSupplied ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  check_expected_areq (int,TYPE_2__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int pg_GSS_continue (TYPE_2__*,int) ; 
 int pg_GSS_startup (TYPE_2__*,int) ; 
 int pg_SASL_continue (TYPE_2__*,int,int) ; 
 int pg_SASL_init (TYPE_2__*,int) ; 
 int pg_SSPI_continue (TYPE_2__*,int) ; 
 int pg_SSPI_startup (TYPE_2__*,int,int) ; 
 int pg_local_sendauth (TYPE_2__*) ; 
 int pg_password_sendauth (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  pg_strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pglock_thread () ; 
 int /*<<< orphan*/  pgunlock_thread () ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_3__*,char*,...) ; 

int
pg_fe_sendauth(AuthRequest areq, int payloadlen, PGconn *conn)
{
	if (!check_expected_areq(areq, conn))
		return STATUS_ERROR;

	switch (areq)
	{
		case AUTH_REQ_OK:
			break;

		case AUTH_REQ_KRB4:
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("Kerberos 4 authentication not supported\n"));
			return STATUS_ERROR;

		case AUTH_REQ_KRB5:
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("Kerberos 5 authentication not supported\n"));
			return STATUS_ERROR;

#if defined(ENABLE_GSS) || defined(ENABLE_SSPI)
		case AUTH_REQ_GSS:
#if !defined(ENABLE_SSPI)
			/* no native SSPI, so use GSSAPI library for it */
		case AUTH_REQ_SSPI:
#endif
			{
				int			r;

				pglock_thread();

				/*
				 * If we have both GSS and SSPI support compiled in, use SSPI
				 * support by default. This is overridable by a connection
				 * string parameter. Note that when using SSPI we still leave
				 * the negotiate parameter off, since we want SSPI to use the
				 * GSSAPI kerberos protocol. For actual SSPI negotiate
				 * protocol, we use AUTH_REQ_SSPI.
				 */
#if defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				if (conn->gsslib && (pg_strcasecmp(conn->gsslib, "gssapi") == 0))
					r = pg_GSS_startup(conn, payloadlen);
				else
					r = pg_SSPI_startup(conn, 0, payloadlen);
#elif defined(ENABLE_GSS) && !defined(ENABLE_SSPI)
				r = pg_GSS_startup(conn, payloadlen);
#elif !defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				r = pg_SSPI_startup(conn, 0, payloadlen);
#endif
				if (r != STATUS_OK)
				{
					/* Error message already filled in. */
					pgunlock_thread();
					return STATUS_ERROR;
				}
				pgunlock_thread();
			}
			break;

		case AUTH_REQ_GSS_CONT:
			{
				int			r;

				pglock_thread();
#if defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				if (conn->usesspi)
					r = pg_SSPI_continue(conn, payloadlen);
				else
					r = pg_GSS_continue(conn, payloadlen);
#elif defined(ENABLE_GSS) && !defined(ENABLE_SSPI)
				r = pg_GSS_continue(conn, payloadlen);
#elif !defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				r = pg_SSPI_continue(conn, payloadlen);
#endif
				if (r != STATUS_OK)
				{
					/* Error message already filled in. */
					pgunlock_thread();
					return STATUS_ERROR;
				}
				pgunlock_thread();
			}
			break;
#else							/* defined(ENABLE_GSS) || defined(ENABLE_SSPI) */
			/* No GSSAPI *or* SSPI support */
		case AUTH_REQ_GSS:
		case AUTH_REQ_GSS_CONT:
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("GSSAPI authentication not supported\n"));
			return STATUS_ERROR;
#endif							/* defined(ENABLE_GSS) || defined(ENABLE_SSPI) */

#ifdef ENABLE_SSPI
		case AUTH_REQ_SSPI:

			/*
			 * SSPI has its own startup message so libpq can decide which
			 * method to use. Indicate to pg_SSPI_startup that we want SSPI
			 * negotiation instead of Kerberos.
			 */
			pglock_thread();
			if (pg_SSPI_startup(conn, 1, payloadlen) != STATUS_OK)
			{
				/* Error message already filled in. */
				pgunlock_thread();
				return STATUS_ERROR;
			}
			pgunlock_thread();
			break;
#else

			/*
			 * No SSPI support. However, if we have GSSAPI but not SSPI
			 * support, AUTH_REQ_SSPI will have been handled in the codepath
			 * for AUTH_REQ_GSS above, so don't duplicate the case label in
			 * that case.
			 */
#if !defined(ENABLE_GSS)
		case AUTH_REQ_SSPI:
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("SSPI authentication not supported\n"));
			return STATUS_ERROR;
#endif							/* !define(ENABLE_GSS) */
#endif							/* ENABLE_SSPI */


		case AUTH_REQ_CRYPT:
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("Crypt authentication not supported\n"));
			return STATUS_ERROR;

		case AUTH_REQ_MD5:
		case AUTH_REQ_PASSWORD:
			{
				char	   *password;

				conn->password_needed = true;
				password = conn->connhost[conn->whichhost].password;
				if (password == NULL)
					password = conn->pgpass;
				if (password == NULL || password[0] == '\0')
				{
					printfPQExpBuffer(&conn->errorMessage,
									  PQnoPasswordSupplied);
					return STATUS_ERROR;
				}
				if (pg_password_sendauth(conn, password, areq) != STATUS_OK)
				{
					printfPQExpBuffer(&conn->errorMessage,
									  "fe_sendauth: error sending password authentication\n");
					return STATUS_ERROR;
				}
				break;
			}

		case AUTH_REQ_SASL:

			/*
			 * The request contains the name (as assigned by IANA) of the
			 * authentication mechanism.
			 */
			if (pg_SASL_init(conn, payloadlen) != STATUS_OK)
			{
				/* pg_SASL_init already set the error message */
				return STATUS_ERROR;
			}
			break;

		case AUTH_REQ_SASL_CONT:
		case AUTH_REQ_SASL_FIN:
			if (conn->sasl_state == NULL)
			{
				printfPQExpBuffer(&conn->errorMessage,
								  "fe_sendauth: invalid authentication request from server: AUTH_REQ_SASL_CONT without AUTH_REQ_SASL\n");
				return STATUS_ERROR;
			}
			if (pg_SASL_continue(conn, payloadlen,
								 (areq == AUTH_REQ_SASL_FIN)) != STATUS_OK)
			{
				/* Use error message, if set already */
				if (conn->errorMessage.len == 0)
					printfPQExpBuffer(&conn->errorMessage,
									  "fe_sendauth: error in SASL authentication\n");
				return STATUS_ERROR;
			}
			break;

		case AUTH_REQ_SCM_CREDS:
			if (pg_local_sendauth(conn) != STATUS_OK)
				return STATUS_ERROR;
			break;

		default:
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("authentication method %u not supported\n"), areq);
			return STATUS_ERROR;
	}

	return STATUS_OK;
}