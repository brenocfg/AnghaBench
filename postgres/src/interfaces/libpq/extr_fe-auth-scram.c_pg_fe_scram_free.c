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
struct TYPE_3__ {struct TYPE_3__* server_final_message; struct TYPE_3__* nonce; struct TYPE_3__* salt; struct TYPE_3__* server_first_message; struct TYPE_3__* client_final_message_without_proof; struct TYPE_3__* client_first_message_bare; struct TYPE_3__* client_nonce; struct TYPE_3__* sasl_mechanism; struct TYPE_3__* password; } ;
typedef  TYPE_1__ fe_scram_state ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
pg_fe_scram_free(void *opaq)
{
	fe_scram_state *state = (fe_scram_state *) opaq;

	if (state->password)
		free(state->password);
	if (state->sasl_mechanism)
		free(state->sasl_mechanism);

	/* client messages */
	if (state->client_nonce)
		free(state->client_nonce);
	if (state->client_first_message_bare)
		free(state->client_first_message_bare);
	if (state->client_final_message_without_proof)
		free(state->client_final_message_without_proof);

	/* first message from server */
	if (state->server_first_message)
		free(state->server_first_message);
	if (state->salt)
		free(state->salt);
	if (state->nonce)
		free(state->nonce);

	/* final message from server */
	if (state->server_final_message)
		free(state->server_final_message);

	free(state);
}