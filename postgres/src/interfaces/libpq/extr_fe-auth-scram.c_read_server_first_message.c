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
struct TYPE_4__ {char* client_nonce; int iterations; int /*<<< orphan*/  saltlen; int /*<<< orphan*/ * salt; int /*<<< orphan*/ * nonce; int /*<<< orphan*/ * server_first_message; TYPE_2__* conn; } ;
typedef  TYPE_1__ fe_scram_state ;
struct TYPE_5__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 int pg_b64_dec_len (scalar_t__) ; 
 int /*<<< orphan*/  pg_b64_decode (char*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* read_attr_value (char**,char,int /*<<< orphan*/ *) ; 
 void* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static bool
read_server_first_message(fe_scram_state *state, char *input)
{
	PGconn	   *conn = state->conn;
	char	   *iterations_str;
	char	   *endptr;
	char	   *encoded_salt;
	char	   *nonce;
	int			decoded_salt_len;

	state->server_first_message = strdup(input);
	if (state->server_first_message == NULL)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return false;
	}

	/* parse the message */
	nonce = read_attr_value(&input, 'r',
							&conn->errorMessage);
	if (nonce == NULL)
	{
		/* read_attr_value() has generated an error string */
		return false;
	}

	/* Verify immediately that the server used our part of the nonce */
	if (strlen(nonce) < strlen(state->client_nonce) ||
		memcmp(nonce, state->client_nonce, strlen(state->client_nonce)) != 0)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("invalid SCRAM response (nonce mismatch)\n"));
		return false;
	}

	state->nonce = strdup(nonce);
	if (state->nonce == NULL)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return false;
	}

	encoded_salt = read_attr_value(&input, 's', &conn->errorMessage);
	if (encoded_salt == NULL)
	{
		/* read_attr_value() has generated an error string */
		return false;
	}
	decoded_salt_len = pg_b64_dec_len(strlen(encoded_salt));
	state->salt = malloc(decoded_salt_len);
	if (state->salt == NULL)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return false;
	}
	state->saltlen = pg_b64_decode(encoded_salt,
								   strlen(encoded_salt),
								   state->salt,
								   decoded_salt_len);
	if (state->saltlen < 0)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("malformed SCRAM message (invalid salt)\n"));
		return false;
	}

	iterations_str = read_attr_value(&input, 'i', &conn->errorMessage);
	if (iterations_str == NULL)
	{
		/* read_attr_value() has generated an error string */
		return false;
	}
	state->iterations = strtol(iterations_str, &endptr, 10);
	if (*endptr != '\0' || state->iterations < 1)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("malformed SCRAM message (invalid iteration count)\n"));
		return false;
	}

	if (*input != '\0')
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("malformed SCRAM message (garbage at end of server-first-message)\n"));

	return true;
}