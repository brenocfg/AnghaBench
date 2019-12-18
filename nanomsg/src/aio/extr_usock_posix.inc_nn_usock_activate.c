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
struct nn_usock {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_USOCK_ACTION_ACTIVATE ; 
 int /*<<< orphan*/  nn_fsm_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nn_usock_activate (struct nn_usock *self)
{
    nn_fsm_action (&self->fsm, NN_USOCK_ACTION_ACTIVATE);
}