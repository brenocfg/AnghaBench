#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* data; int len; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  Port ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_REQ_SASL ; 
 int /*<<< orphan*/  AUTH_REQ_SASL_CONT ; 
 int /*<<< orphan*/  AUTH_REQ_SASL_FIN ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int EOF ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  FrontendProtocol ; 
 int /*<<< orphan*/  PG_MAX_SASL_MESSAGE_LENGTH ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int SASL_EXCHANGE_CONTINUE ; 
 int SASL_EXCHANGE_SUCCESS ; 
 int STATUS_EOF ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_be_scram_exchange (void*,char const*,int,char**,int*,char**) ; 
 int /*<<< orphan*/  pg_be_scram_get_mechanisms (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* pg_be_scram_init (int /*<<< orphan*/ *,char const*,char*) ; 
 int pq_getbyte () ; 
 scalar_t__ pq_getmessage (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* pq_getmsgbytes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pq_getmsgend (TYPE_1__*) ; 
 int pq_getmsgint (TYPE_1__*,int) ; 
 char* pq_getmsgrawstring (TYPE_1__*) ; 
 int /*<<< orphan*/  pq_startmsgread () ; 
 int /*<<< orphan*/  sendAuthRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
CheckSCRAMAuth(Port *port, char *shadow_pass, char **logdetail)
{
	StringInfoData sasl_mechs;
	int			mtype;
	StringInfoData buf;
	void	   *scram_opaq = NULL;
	char	   *output = NULL;
	int			outputlen = 0;
	const char *input;
	int			inputlen;
	int			result;
	bool		initial;

	/*
	 * SASL auth is not supported for protocol versions before 3, because it
	 * relies on the overall message length word to determine the SASL payload
	 * size in AuthenticationSASLContinue and PasswordMessage messages.  (We
	 * used to have a hard rule that protocol messages must be parsable
	 * without relying on the length word, but we hardly care about older
	 * protocol version anymore.)
	 */
	if (PG_PROTOCOL_MAJOR(FrontendProtocol) < 3)
		ereport(FATAL,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("SASL authentication is not supported in protocol version 2")));

	/*
	 * Send the SASL authentication request to user.  It includes the list of
	 * authentication mechanisms that are supported.
	 */
	initStringInfo(&sasl_mechs);

	pg_be_scram_get_mechanisms(port, &sasl_mechs);
	/* Put another '\0' to mark that list is finished. */
	appendStringInfoChar(&sasl_mechs, '\0');

	sendAuthRequest(port, AUTH_REQ_SASL, sasl_mechs.data, sasl_mechs.len);
	pfree(sasl_mechs.data);

	/*
	 * Loop through SASL message exchange.  This exchange can consist of
	 * multiple messages sent in both directions.  First message is always
	 * from the client.  All messages from client to server are password
	 * packets (type 'p').
	 */
	initial = true;
	do
	{
		pq_startmsgread();
		mtype = pq_getbyte();
		if (mtype != 'p')
		{
			/* Only log error if client didn't disconnect. */
			if (mtype != EOF)
			{
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("expected SASL response, got message type %d",
								mtype)));
			}
			else
				return STATUS_EOF;
		}

		/* Get the actual SASL message */
		initStringInfo(&buf);
		if (pq_getmessage(&buf, PG_MAX_SASL_MESSAGE_LENGTH))
		{
			/* EOF - pq_getmessage already logged error */
			pfree(buf.data);
			return STATUS_ERROR;
		}

		elog(DEBUG4, "processing received SASL response of length %d", buf.len);

		/*
		 * The first SASLInitialResponse message is different from the others.
		 * It indicates which SASL mechanism the client selected, and contains
		 * an optional Initial Client Response payload.  The subsequent
		 * SASLResponse messages contain just the SASL payload.
		 */
		if (initial)
		{
			const char *selected_mech;

			selected_mech = pq_getmsgrawstring(&buf);

			/*
			 * Initialize the status tracker for message exchanges.
			 *
			 * If the user doesn't exist, or doesn't have a valid password, or
			 * it's expired, we still go through the motions of SASL
			 * authentication, but tell the authentication method that the
			 * authentication is "doomed". That is, it's going to fail, no
			 * matter what.
			 *
			 * This is because we don't want to reveal to an attacker what
			 * usernames are valid, nor which users have a valid password.
			 */
			scram_opaq = pg_be_scram_init(port, selected_mech, shadow_pass);

			inputlen = pq_getmsgint(&buf, 4);
			if (inputlen == -1)
				input = NULL;
			else
				input = pq_getmsgbytes(&buf, inputlen);

			initial = false;
		}
		else
		{
			inputlen = buf.len;
			input = pq_getmsgbytes(&buf, buf.len);
		}
		pq_getmsgend(&buf);

		/*
		 * The StringInfo guarantees that there's a \0 byte after the
		 * response.
		 */
		Assert(input == NULL || input[inputlen] == '\0');

		/*
		 * we pass 'logdetail' as NULL when doing a mock authentication,
		 * because we should already have a better error message in that case
		 */
		result = pg_be_scram_exchange(scram_opaq, input, inputlen,
									  &output, &outputlen,
									  logdetail);

		/* input buffer no longer used */
		pfree(buf.data);

		if (output)
		{
			/*
			 * Negotiation generated data to be sent to the client.
			 */
			elog(DEBUG4, "sending SASL challenge of length %u", outputlen);

			if (result == SASL_EXCHANGE_SUCCESS)
				sendAuthRequest(port, AUTH_REQ_SASL_FIN, output, outputlen);
			else
				sendAuthRequest(port, AUTH_REQ_SASL_CONT, output, outputlen);

			pfree(output);
		}
	} while (result == SASL_EXCHANGE_CONTINUE);

	/* Oops, Something bad happened */
	if (result != SASL_EXCHANGE_SUCCESS)
	{
		return STATUS_ERROR;
	}

	return STATUS_OK;
}