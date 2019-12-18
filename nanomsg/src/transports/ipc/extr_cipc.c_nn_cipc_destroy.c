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
struct nn_cipc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/  retry; int /*<<< orphan*/  sipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_backoff_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_free (struct nn_cipc*) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sipc_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_cipc_destroy (void *self)
{
    struct nn_cipc *cipc = self;

    nn_sipc_term (&cipc->sipc);
    nn_backoff_term (&cipc->retry);
    nn_usock_term (&cipc->usock);
    nn_fsm_term (&cipc->fsm);

    nn_free (cipc);
}