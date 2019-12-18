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
struct TYPE_5__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  sasl_state; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  pg_fe_scram_exchange (int /*<<< orphan*/ ,char*,int,char**,int*,int*,int*) ; 
 scalar_t__ pqGetnchar (char*,int,TYPE_1__*) ; 
 int pqPacketSend (TYPE_1__*,char,char*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
pg_SASL_continue(PGconn *conn, int payloadlen, bool final)
{
	char	   *output;
	int			outputlen;
	bool		done;
	bool		success;
	int			res;
	char	   *challenge;

	/* Read the SASL challenge from the AuthenticationSASLContinue message. */
	challenge = malloc(payloadlen + 1);
	if (!challenge)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory allocating SASL buffer (%d)\n"),
						  payloadlen);
		return STATUS_ERROR;
	}

	if (pqGetnchar(challenge, payloadlen, conn))
	{
		free(challenge);
		return STATUS_ERROR;
	}
	/* For safety and convenience, ensure the buffer is NULL-terminated. */
	challenge[payloadlen] = '\0';

	pg_fe_scram_exchange(conn->sasl_state,
						 challenge, payloadlen,
						 &output, &outputlen,
						 &done, &success);
	free(challenge);			/* don't need the input anymore */

	if (final && !done)
	{
		if (outputlen != 0)
			free(output);

		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("AuthenticationSASLFinal received from server, but SASL authentication was not completed\n"));
		return STATUS_ERROR;
	}
	if (outputlen != 0)
	{
		/*
		 * Send the SASL response to the server.
		 */
		res = pqPacketSend(conn, 'p', output, outputlen);
		free(output);

		if (res != STATUS_OK)
			return STATUS_ERROR;
	}

	if (done && !success)
		return STATUS_ERROR;

	return STATUS_OK;
}