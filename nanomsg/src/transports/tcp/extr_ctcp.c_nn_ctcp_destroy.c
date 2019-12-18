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
struct nn_ctcp {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/  retry; int /*<<< orphan*/  stcp; int /*<<< orphan*/  dns; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_backoff_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_dns_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_free (struct nn_ctcp*) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_stcp_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_ctcp_destroy (void *self)
{
    struct nn_ctcp *ctcp = self;

    nn_dns_term (&ctcp->dns);
    nn_stcp_term (&ctcp->stcp);
    nn_backoff_term (&ctcp->retry);
    nn_usock_term (&ctcp->usock);
    nn_fsm_term (&ctcp->fsm);

    nn_free (ctcp);
}