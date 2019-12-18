#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nn_bipc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/ * aipc; int /*<<< orphan*/  aipcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BIPC_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_bipc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_free (struct nn_bipc*) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_bipc_destroy (void *self)
{
    struct nn_bipc *bipc = self;

    nn_assert_state (bipc, NN_BIPC_STATE_IDLE);
    nn_list_term (&bipc->aipcs);
    nn_assert (bipc->aipc == NULL);
    nn_usock_term (&bipc->usock);
    nn_fsm_term (&bipc->fsm);

    nn_free (bipc);
}