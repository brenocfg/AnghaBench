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
struct nn_backoff {int minivl; int maxivl; int n; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_timer_init (int /*<<< orphan*/ *,int,struct nn_fsm*) ; 

void nn_backoff_init (struct nn_backoff *self, int src, int minivl, int maxivl,
    struct nn_fsm *owner)
{
    nn_timer_init (&self->timer, src, owner);
    self->minivl = minivl;
    self->maxivl = maxivl;
    self->n = 1;
}