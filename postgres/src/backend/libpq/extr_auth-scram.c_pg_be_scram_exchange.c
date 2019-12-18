#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int state; char* logdetail; int /*<<< orphan*/  doomed; } ;
typedef  TYPE_1__ scram_state ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int SASL_EXCHANGE_CONTINUE ; 
 int SASL_EXCHANGE_FAILURE ; 
 int SASL_EXCHANGE_SUCCESS ; 
 int SCRAM_AUTH_FINISHED ; 
#define  SCRAM_AUTH_INIT 129 
#define  SCRAM_AUTH_SALT_SENT 128 
 char* build_server_final_message (TYPE_1__*) ; 
 char* build_server_first_message (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  read_client_final_message (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  read_client_first_message (TYPE_1__*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  verify_client_proof (TYPE_1__*) ; 
 int /*<<< orphan*/  verify_final_nonce (TYPE_1__*) ; 

int
pg_be_scram_exchange(void *opaq, const char *input, int inputlen,
					 char **output, int *outputlen, char **logdetail)
{
	scram_state *state = (scram_state *) opaq;
	int			result;

	*output = NULL;

	/*
	 * If the client didn't include an "Initial Client Response" in the
	 * SASLInitialResponse message, send an empty challenge, to which the
	 * client will respond with the same data that usually comes in the
	 * Initial Client Response.
	 */
	if (input == NULL)
	{
		Assert(state->state == SCRAM_AUTH_INIT);

		*output = pstrdup("");
		*outputlen = 0;
		return SASL_EXCHANGE_CONTINUE;
	}

	/*
	 * Check that the input length agrees with the string length of the input.
	 * We can ignore inputlen after this.
	 */
	if (inputlen == 0)
		ereport(ERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("malformed SCRAM message"),
				 errdetail("The message is empty.")));
	if (inputlen != strlen(input))
		ereport(ERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("malformed SCRAM message"),
				 errdetail("Message length does not match input length.")));

	switch (state->state)
	{
		case SCRAM_AUTH_INIT:

			/*
			 * Initialization phase.  Receive the first message from client
			 * and be sure that it parsed correctly.  Then send the challenge
			 * to the client.
			 */
			read_client_first_message(state, input);

			/* prepare message to send challenge */
			*output = build_server_first_message(state);

			state->state = SCRAM_AUTH_SALT_SENT;
			result = SASL_EXCHANGE_CONTINUE;
			break;

		case SCRAM_AUTH_SALT_SENT:

			/*
			 * Final phase for the server.  Receive the response to the
			 * challenge previously sent, verify, and let the client know that
			 * everything went well (or not).
			 */
			read_client_final_message(state, input);

			if (!verify_final_nonce(state))
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("invalid SCRAM response"),
						 errdetail("Nonce does not match.")));

			/*
			 * Now check the final nonce and the client proof.
			 *
			 * If we performed a "mock" authentication that we knew would fail
			 * from the get go, this is where we fail.
			 *
			 * The SCRAM specification includes an error code,
			 * "invalid-proof", for authentication failure, but it also allows
			 * erroring out in an application-specific way.  We choose to do
			 * the latter, so that the error message for invalid password is
			 * the same for all authentication methods.  The caller will call
			 * ereport(), when we return SASL_EXCHANGE_FAILURE with no output.
			 *
			 * NB: the order of these checks is intentional.  We calculate the
			 * client proof even in a mock authentication, even though it's
			 * bound to fail, to thwart timing attacks to determine if a role
			 * with the given name exists or not.
			 */
			if (!verify_client_proof(state) || state->doomed)
			{
				result = SASL_EXCHANGE_FAILURE;
				break;
			}

			/* Build final message for client */
			*output = build_server_final_message(state);

			/* Success! */
			result = SASL_EXCHANGE_SUCCESS;
			state->state = SCRAM_AUTH_FINISHED;
			break;

		default:
			elog(ERROR, "invalid SCRAM exchange state");
			result = SASL_EXCHANGE_FAILURE;
	}

	if (result == SASL_EXCHANGE_FAILURE && state->logdetail && logdetail)
		*logdetail = state->logdetail;

	if (*output)
		*outputlen = strlen(*output);

	return result;
}