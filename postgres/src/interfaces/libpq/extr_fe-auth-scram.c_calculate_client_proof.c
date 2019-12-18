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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  scram_HMAC_ctx ;
struct TYPE_3__ {char const* client_first_message_bare; char const* server_first_message; int /*<<< orphan*/  SaltedPassword; int /*<<< orphan*/  iterations; int /*<<< orphan*/  saltlen; int /*<<< orphan*/  salt; int /*<<< orphan*/  password; } ;
typedef  TYPE_1__ fe_scram_state ;

/* Variables and functions */
 int SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  scram_ClientKey (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  scram_H (int*,int,int*) ; 
 int /*<<< orphan*/  scram_HMAC_final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_HMAC_init (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  scram_HMAC_update (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  scram_SaltedPassword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
calculate_client_proof(fe_scram_state *state,
					   const char *client_final_message_without_proof,
					   uint8 *result)
{
	uint8		StoredKey[SCRAM_KEY_LEN];
	uint8		ClientKey[SCRAM_KEY_LEN];
	uint8		ClientSignature[SCRAM_KEY_LEN];
	int			i;
	scram_HMAC_ctx ctx;

	/*
	 * Calculate SaltedPassword, and store it in 'state' so that we can reuse
	 * it later in verify_server_signature.
	 */
	scram_SaltedPassword(state->password, state->salt, state->saltlen,
						 state->iterations, state->SaltedPassword);

	scram_ClientKey(state->SaltedPassword, ClientKey);
	scram_H(ClientKey, SCRAM_KEY_LEN, StoredKey);

	scram_HMAC_init(&ctx, StoredKey, SCRAM_KEY_LEN);
	scram_HMAC_update(&ctx,
					  state->client_first_message_bare,
					  strlen(state->client_first_message_bare));
	scram_HMAC_update(&ctx, ",", 1);
	scram_HMAC_update(&ctx,
					  state->server_first_message,
					  strlen(state->server_first_message));
	scram_HMAC_update(&ctx, ",", 1);
	scram_HMAC_update(&ctx,
					  client_final_message_without_proof,
					  strlen(client_final_message_without_proof));
	scram_HMAC_final(ClientSignature, &ctx);

	for (i = 0; i < SCRAM_KEY_LEN; i++)
		result[i] = ClientKey[i] ^ ClientSignature[i];
}