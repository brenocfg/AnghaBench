#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int state; TYPE_2__* conn; } ;
typedef  TYPE_1__ fe_scram_state ;
struct TYPE_9__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int FE_SCRAM_FINISHED ; 
#define  FE_SCRAM_INIT 130 
#define  FE_SCRAM_NONCE_SENT 129 
#define  FE_SCRAM_PROOF_SENT 128 
 char* build_client_final_message (TYPE_1__*) ; 
 char* build_client_first_message (TYPE_1__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_server_final_message (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  read_server_first_message (TYPE_1__*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  verify_server_signature (TYPE_1__*) ; 

void
pg_fe_scram_exchange(void *opaq, char *input, int inputlen,
					 char **output, int *outputlen,
					 bool *done, bool *success)
{
	fe_scram_state *state = (fe_scram_state *) opaq;
	PGconn	   *conn = state->conn;

	*done = false;
	*success = false;
	*output = NULL;
	*outputlen = 0;

	/*
	 * Check that the input length agrees with the string length of the input.
	 * We can ignore inputlen after this.
	 */
	if (state->state != FE_SCRAM_INIT)
	{
		if (inputlen == 0)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("malformed SCRAM message (empty message)\n"));
			goto error;
		}
		if (inputlen != strlen(input))
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("malformed SCRAM message (length mismatch)\n"));
			goto error;
		}
	}

	switch (state->state)
	{
		case FE_SCRAM_INIT:
			/* Begin the SCRAM handshake, by sending client nonce */
			*output = build_client_first_message(state);
			if (*output == NULL)
				goto error;

			*outputlen = strlen(*output);
			*done = false;
			state->state = FE_SCRAM_NONCE_SENT;
			break;

		case FE_SCRAM_NONCE_SENT:
			/* Receive salt and server nonce, send response. */
			if (!read_server_first_message(state, input))
				goto error;

			*output = build_client_final_message(state);
			if (*output == NULL)
				goto error;

			*outputlen = strlen(*output);
			*done = false;
			state->state = FE_SCRAM_PROOF_SENT;
			break;

		case FE_SCRAM_PROOF_SENT:
			/* Receive server signature */
			if (!read_server_final_message(state, input))
				goto error;

			/*
			 * Verify server signature, to make sure we're talking to the
			 * genuine server.
			 */
			if (verify_server_signature(state))
				*success = true;
			else
			{
				*success = false;
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("incorrect server signature\n"));
			}
			*done = true;
			state->state = FE_SCRAM_FINISHED;
			break;

		default:
			/* shouldn't happen */
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("invalid SCRAM exchange state\n"));
			goto error;
	}
	return;

error:
	*done = true;
	*success = false;
	return;
}