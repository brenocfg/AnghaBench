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
struct nn_fsm_owner {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fsm_swap_owner (int /*<<< orphan*/ *,struct nn_fsm_owner*) ; 

void nn_usock_swap_owner (struct nn_usock *self, struct nn_fsm_owner *owner)
{
    nn_fsm_swap_owner (&self->fsm, owner);
}