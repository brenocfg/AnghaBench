#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* client_nonce; void* client_first_message_bare; int /*<<< orphan*/  sasl_mechanism; TYPE_3__* conn; } ;
typedef  TYPE_1__ fe_scram_state ;
struct TYPE_13__ {char* channel_binding; int /*<<< orphan*/  errorMessage; scalar_t__ ssl_in_use; } ;
struct TYPE_12__ {int len; scalar_t__ data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_3__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 scalar_t__ PQExpBufferDataBroken (TYPE_2__) ; 
 int /*<<< orphan*/  SCRAM_RAW_NONCE_LEN ; 
 int /*<<< orphan*/  SCRAM_SHA_256_PLUS_NAME ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (int) ; 
 int pg_b64_enc_len (int /*<<< orphan*/ ) ; 
 int pg_b64_encode (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pg_strong_random (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strdup (scalar_t__) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

__attribute__((used)) static char *
build_client_first_message(fe_scram_state *state)
{
	PGconn	   *conn = state->conn;
	char		raw_nonce[SCRAM_RAW_NONCE_LEN + 1];
	char	   *result;
	int			channel_info_len;
	int			encoded_len;
	PQExpBufferData buf;

	/*
	 * Generate a "raw" nonce.  This is converted to ASCII-printable form by
	 * base64-encoding it.
	 */
	if (!pg_strong_random(raw_nonce, SCRAM_RAW_NONCE_LEN))
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("could not generate nonce\n"));
		return NULL;
	}

	encoded_len = pg_b64_enc_len(SCRAM_RAW_NONCE_LEN);
	/* don't forget the zero-terminator */
	state->client_nonce = malloc(encoded_len + 1);
	if (state->client_nonce == NULL)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return NULL;
	}
	encoded_len = pg_b64_encode(raw_nonce, SCRAM_RAW_NONCE_LEN,
								state->client_nonce, encoded_len);
	if (encoded_len < 0)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("could not encode nonce\n"));
		return NULL;
	}
	state->client_nonce[encoded_len] = '\0';

	/*
	 * Generate message.  The username is left empty as the backend uses the
	 * value provided by the startup packet.  Also, as this username is not
	 * prepared with SASLprep, the message parsing would fail if it includes
	 * '=' or ',' characters.
	 */

	initPQExpBuffer(&buf);

	/*
	 * First build the gs2-header with channel binding information.
	 */
	if (strcmp(state->sasl_mechanism, SCRAM_SHA_256_PLUS_NAME) == 0)
	{
		Assert(conn->ssl_in_use);
		appendPQExpBufferStr(&buf, "p=tls-server-end-point");
	}
#ifdef HAVE_PGTLS_GET_PEER_CERTIFICATE_HASH
	else if (conn->channel_binding[0] != 'd' && /* disable */
			 conn->ssl_in_use)
	{
		/*
		 * Client supports channel binding, but thinks the server does not.
		 */
		appendPQExpBufferChar(&buf, 'y');
	}
#endif
	else
	{
		/*
		 * Client does not support channel binding, or has disabled it.
		 */
		appendPQExpBufferChar(&buf, 'n');
	}

	if (PQExpBufferDataBroken(buf))
		goto oom_error;

	channel_info_len = buf.len;

	appendPQExpBuffer(&buf, ",,n=,r=%s", state->client_nonce);
	if (PQExpBufferDataBroken(buf))
		goto oom_error;

	/*
	 * The first message content needs to be saved without channel binding
	 * information.
	 */
	state->client_first_message_bare = strdup(buf.data + channel_info_len + 2);
	if (!state->client_first_message_bare)
		goto oom_error;

	result = strdup(buf.data);
	if (result == NULL)
		goto oom_error;

	termPQExpBuffer(&buf);
	return result;

oom_error:
	termPQExpBuffer(&buf);
	printfPQExpBuffer(&conn->errorMessage,
					  libpq_gettext("out of memory\n"));
	return NULL;
}