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
struct nn_btcp {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/ * atcp; int /*<<< orphan*/  atcps; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BTCP_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_btcp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_free (struct nn_btcp*) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_btcp_destroy (void *self)
{
    struct nn_btcp *btcp = self;

    nn_assert_state (btcp, NN_BTCP_STATE_IDLE);
    nn_list_term (&btcp->atcps);
    nn_assert (btcp->atcp == NULL);
    nn_usock_term (&btcp->usock);
    nn_fsm_term (&btcp->fsm);

    nn_free (btcp);
}