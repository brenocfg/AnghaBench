#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ServerSignature; int /*<<< orphan*/  server_final_message; TYPE_2__* conn; } ;
typedef  TYPE_1__ fe_scram_state ;
struct TYPE_5__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int pg_b64_dec_len (int /*<<< orphan*/ ) ; 
 int pg_b64_decode (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 char* read_attr_value (char**,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool
read_server_final_message(fe_scram_state *state, char *input)
{
	PGconn	   *conn = state->conn;
	char	   *encoded_server_signature;
	char	   *decoded_server_signature;
	int			server_signature_len;

	state->server_final_message = strdup(input);
	if (!state->server_final_message)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return false;
	}

	/* Check for error result. */
	if (*input == 'e')
	{
		char	   *errmsg = read_attr_value(&input, 'e',
											 &conn->errorMessage);

		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("error received from server in SCRAM exchange: %s\n"),
						  errmsg);
		return false;
	}

	/* Parse the message. */
	encoded_server_signature = read_attr_value(&input, 'v',
											   &conn->errorMessage);
	if (encoded_server_signature == NULL)
	{
		/* read_attr_value() has generated an error message */
		return false;
	}

	if (*input != '\0')
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("malformed SCRAM message (garbage at end of server-final-message)\n"));

	server_signature_len = pg_b64_dec_len(strlen(encoded_server_signature));
	decoded_server_signature = malloc(server_signature_len);
	if (!decoded_server_signature)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return false;
	}

	server_signature_len = pg_b64_decode(encoded_server_signature,
										 strlen(encoded_server_signature),
										 decoded_server_signature,
										 server_signature_len);
	if (server_signature_len != SCRAM_KEY_LEN)
	{
		free(decoded_server_signature);
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("malformed SCRAM message (invalid server signature)\n"));
		return false;
	}
	memcpy(state->ServerSignature, decoded_server_signature, SCRAM_KEY_LEN);
	free(decoded_server_signature);

	return true;
}