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
struct TYPE_3__ {char* client_first_message_bare; char* server_first_message; char* client_final_message_without_proof; int* ClientProof; int /*<<< orphan*/  StoredKey; } ;
typedef  TYPE_1__ scram_state ;
typedef  int /*<<< orphan*/  scram_HMAC_ctx ;

/* Variables and functions */
 int SCRAM_KEY_LEN ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scram_H (int*,int,int*) ; 
 int /*<<< orphan*/  scram_HMAC_final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_HMAC_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scram_HMAC_update (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool
verify_client_proof(scram_state *state)
{
	uint8		ClientSignature[SCRAM_KEY_LEN];
	uint8		ClientKey[SCRAM_KEY_LEN];
	uint8		client_StoredKey[SCRAM_KEY_LEN];
	scram_HMAC_ctx ctx;
	int			i;

	/* calculate ClientSignature */
	scram_HMAC_init(&ctx, state->StoredKey, SCRAM_KEY_LEN);
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
	scram_HMAC_final(ClientSignature, &ctx);

	/* Extract the ClientKey that the client calculated from the proof */
	for (i = 0; i < SCRAM_KEY_LEN; i++)
		ClientKey[i] = state->ClientProof[i] ^ ClientSignature[i];

	/* Hash it one more time, and compare with StoredKey */
	scram_H(ClientKey, SCRAM_KEY_LEN, client_StoredKey);

	if (memcmp(client_StoredKey, state->StoredKey, SCRAM_KEY_LEN) != 0)
		return false;

	return true;
}