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
struct nn_dns {int /*<<< orphan*/  fsm; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_DNS_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_dns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 

void nn_dns_term (struct nn_dns *self)
{
    nn_assert_state (self, NN_DNS_STATE_IDLE);

    nn_fsm_event_term (&self->done);
    nn_fsm_term (&self->fsm);
}