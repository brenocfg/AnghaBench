#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {char* channel_binding; int password_needed; size_t whichhost; char* pgpass; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  sasl_state; TYPE_1__* connhost; scalar_t__ ssl_in_use; } ;
struct TYPE_18__ {char* data; } ;
struct TYPE_17__ {char* password; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_3__ PGconn ;

/* Variables and functions */
 scalar_t__ PQExpBufferDataBroken (TYPE_2__) ; 
 char* PQnoPasswordSupplied ; 
 char* SCRAM_SHA_256_NAME ; 
 char* SCRAM_SHA_256_PLUS_NAME ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 char* libpq_gettext (char*) ; 
 int /*<<< orphan*/  pg_fe_scram_exchange (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char**,int*,int*,int*) ; 
 int /*<<< orphan*/  pg_fe_scram_init (TYPE_3__*,char*,char const*) ; 
 scalar_t__ pqFlush (TYPE_3__*) ; 
 scalar_t__ pqGets (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ pqPutInt (int,int,TYPE_3__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_3__*) ; 
 scalar_t__ pqPutMsgStart (char,int,TYPE_3__*) ; 
 scalar_t__ pqPutnchar (char*,int,TYPE_3__*) ; 
 scalar_t__ pqPuts (char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

__attribute__((used)) static int
pg_SASL_init(PGconn *conn, int payloadlen)
{
	char	   *initialresponse = NULL;
	int			initialresponselen;
	bool		done;
	bool		success;
	const char *selected_mechanism;
	PQExpBufferData mechanism_buf;
	char	   *password;

	initPQExpBuffer(&mechanism_buf);

	if (conn->channel_binding[0] == 'r' &&	/* require */
		!conn->ssl_in_use)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("Channel binding required, but SSL not in use\n"));
		goto error;
	}

	if (conn->sasl_state)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("duplicate SASL authentication request\n"));
		goto error;
	}

	/*
	 * Parse the list of SASL authentication mechanisms in the
	 * AuthenticationSASL message, and select the best mechanism that we
	 * support.  SCRAM-SHA-256-PLUS and SCRAM-SHA-256 are the only ones
	 * supported at the moment, listed by order of decreasing importance.
	 */
	selected_mechanism = NULL;
	for (;;)
	{
		if (pqGets(&mechanism_buf, conn))
		{
			printfPQExpBuffer(&conn->errorMessage,
							  "fe_sendauth: invalid authentication request from server: invalid list of authentication mechanisms\n");
			goto error;
		}
		if (PQExpBufferDataBroken(mechanism_buf))
			goto oom_error;

		/* An empty string indicates end of list */
		if (mechanism_buf.data[0] == '\0')
			break;

		/*
		 * Select the mechanism to use.  Pick SCRAM-SHA-256-PLUS over anything
		 * else if a channel binding type is set and if the client supports it
		 * (and did not set channel_binding=disable). Pick SCRAM-SHA-256 if
		 * nothing else has already been picked.  If we add more mechanisms, a
		 * more refined priority mechanism might become necessary.
		 */
		if (strcmp(mechanism_buf.data, SCRAM_SHA_256_PLUS_NAME) == 0)
		{
			if (conn->ssl_in_use)
			{
				/* The server has offered SCRAM-SHA-256-PLUS. */

#ifdef HAVE_PGTLS_GET_PEER_CERTIFICATE_HASH
				/*
				 * The client supports channel binding, which is chosen if
				 * channel_binding is not disabled.
				 */
				if (conn->channel_binding[0] != 'd')	/* disable */
					selected_mechanism = SCRAM_SHA_256_PLUS_NAME;
#else
				/*
				 * The client does not support channel binding.  If it is
				 * required, complain immediately instead of the error below
				 * which would be confusing as the server is publishing
				 * SCRAM-SHA-256-PLUS.
				 */
				if (conn->channel_binding[0] == 'r')	/* require */
				{
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("channel binding is required, but client does not support it\n"));
					goto error;
				}
#endif
			}
			else
			{
				/*
				 * The server offered SCRAM-SHA-256-PLUS, but the connection
				 * is not SSL-encrypted. That's not sane. Perhaps SSL was
				 * stripped by a proxy? There's no point in continuing,
				 * because the server will reject the connection anyway if we
				 * try authenticate without channel binding even though both
				 * the client and server supported it. The SCRAM exchange
				 * checks for that, to prevent downgrade attacks.
				 */
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("server offered SCRAM-SHA-256-PLUS authentication over a non-SSL connection\n"));
				goto error;
			}
		}
		else if (strcmp(mechanism_buf.data, SCRAM_SHA_256_NAME) == 0 &&
				 !selected_mechanism)
			selected_mechanism = SCRAM_SHA_256_NAME;
	}

	if (!selected_mechanism)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("none of the server's SASL authentication mechanisms are supported\n"));
		goto error;
	}

	if (conn->channel_binding[0] == 'r' &&	/* require */
		strcmp(selected_mechanism, SCRAM_SHA_256_PLUS_NAME) != 0)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("channel binding is required, but server did not offer an authentication method that supports channel binding\n"));
		goto error;
	}

	/*
	 * Now that the SASL mechanism has been chosen for the exchange,
	 * initialize its state information.
	 */

	/*
	 * First, select the password to use for the exchange, complaining if
	 * there isn't one.  Currently, all supported SASL mechanisms require a
	 * password, so we can just go ahead here without further distinction.
	 */
	conn->password_needed = true;
	password = conn->connhost[conn->whichhost].password;
	if (password == NULL)
		password = conn->pgpass;
	if (password == NULL || password[0] == '\0')
	{
		printfPQExpBuffer(&conn->errorMessage,
						  PQnoPasswordSupplied);
		goto error;
	}

	/*
	 * Initialize the SASL state information with all the information gathered
	 * during the initial exchange.
	 *
	 * Note: Only tls-unique is supported for the moment.
	 */
	conn->sasl_state = pg_fe_scram_init(conn,
										password,
										selected_mechanism);
	if (!conn->sasl_state)
		goto oom_error;

	/* Get the mechanism-specific Initial Client Response, if any */
	pg_fe_scram_exchange(conn->sasl_state,
						 NULL, -1,
						 &initialresponse, &initialresponselen,
						 &done, &success);

	if (done && !success)
		goto error;

	/*
	 * Build a SASLInitialResponse message, and send it.
	 */
	if (pqPutMsgStart('p', true, conn))
		goto error;
	if (pqPuts(selected_mechanism, conn))
		goto error;
	if (initialresponse)
	{
		if (pqPutInt(initialresponselen, 4, conn))
			goto error;
		if (pqPutnchar(initialresponse, initialresponselen, conn))
			goto error;
	}
	if (pqPutMsgEnd(conn))
		goto error;
	if (pqFlush(conn))
		goto error;

	termPQExpBuffer(&mechanism_buf);
	if (initialresponse)
		free(initialresponse);

	return STATUS_OK;

error:
	termPQExpBuffer(&mechanism_buf);
	if (initialresponse)
		free(initialresponse);
	return STATUS_ERROR;

oom_error:
	termPQExpBuffer(&mechanism_buf);
	if (initialresponse)
		free(initialresponse);
	printfPQExpBuffer(&conn->errorMessage,
					  libpq_gettext("out of memory\n"));
	return STATUS_ERROR;
}