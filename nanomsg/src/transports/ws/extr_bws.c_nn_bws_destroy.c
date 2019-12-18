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
struct nn_bws {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/ * aws; int /*<<< orphan*/  awss; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BWS_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_bws*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_free (struct nn_bws*) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_bws_destroy (void *self)
{
    struct nn_bws *bws = self;

    nn_assert_state (bws, NN_BWS_STATE_IDLE);
    nn_list_term (&bws->awss);
    nn_assert (bws->aws == NULL);
    nn_usock_term (&bws->usock);
    nn_fsm_term (&bws->fsm);

    nn_free (bws);
}