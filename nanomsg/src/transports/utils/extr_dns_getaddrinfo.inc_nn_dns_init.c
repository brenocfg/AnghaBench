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
struct nn_fsm {int dummy; } ;
struct nn_dns {int /*<<< orphan*/  done; int /*<<< orphan*/  state; int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_DNS_STATE_IDLE ; 
 int /*<<< orphan*/  nn_dns_handler ; 
 int /*<<< orphan*/  nn_dns_shutdown ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nn_dns*,struct nn_fsm*) ; 

void nn_dns_init (struct nn_dns *self, int src, struct nn_fsm *owner)
{
    nn_fsm_init (&self->fsm, nn_dns_handler, nn_dns_shutdown,
        src, self, owner);
    self->state = NN_DNS_STATE_IDLE;
    nn_fsm_event_init (&self->done);
}