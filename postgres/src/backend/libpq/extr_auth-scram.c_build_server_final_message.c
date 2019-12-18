#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {char* client_first_message_bare; char* server_first_message; char* client_final_message_without_proof; int /*<<< orphan*/  ServerKey; } ;
typedef  TYPE_1__ scram_state ;
typedef  int /*<<< orphan*/  scram_HMAC_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 char* palloc (int) ; 
 int pg_b64_enc_len (int) ; 
 int pg_b64_encode (char const*,int,char*,int) ; 
 char* psprintf (char*,char*) ; 
 int /*<<< orphan*/  scram_HMAC_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_HMAC_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scram_HMAC_update (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
build_server_final_message(scram_state *state)
{
	uint8		ServerSignature[SCRAM_KEY_LEN];
	char	   *server_signature_base64;
	int			siglen;
	scram_HMAC_ctx ctx;

	/* calculate ServerSignature */
	scram_HMAC_init(&ctx, state->ServerKey, SCRAM_KEY_LEN);
	scram_HMAC_update(&ctx,
					  state->client_first_message_bare,
					  strlen(state->client_first_message_bare));
	scram_HMAC_update(&ctx, ",", 1);
	scram_HMAC_update(&ctx,
					  state->server_first_message,
					  strlen(state->server_first_message));
	scram_HMAC_update(&ctx, ",", 1);
	scram_HMAC_update(&ctx,
					  state->client_final_message_without_proof,
					  strlen(state->client_final_message_without_proof));
	scram_HMAC_final(ServerSignature, &ctx);

	siglen = pg_b64_enc_len(SCRAM_KEY_LEN);
	/* don't forget the zero-terminator */
	server_signature_base64 = palloc(siglen + 1);
	siglen = pg_b64_encode((const char *) ServerSignature,
						   SCRAM_KEY_LEN, server_signature_base64,
						   siglen);
	if (siglen < 0)
		elog(ERROR, "could not encode server signature");
	server_signature_base64[siglen] = '\0';

	/*------
	 * The syntax for the server-final-message is: (RFC 5802)
	 *
	 * verifier		   = "v=" base64
	 *					 ;; base-64 encoded ServerSignature.
	 *
	 * server-final-message = (server-error / verifier)
	 *					 ["," extensions]
	 *
	 *------
	 */
	return psprintf("v=%s", server_signature_base64);
}