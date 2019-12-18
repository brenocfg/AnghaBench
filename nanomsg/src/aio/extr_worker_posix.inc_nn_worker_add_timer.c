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
struct nn_worker_timer {int /*<<< orphan*/  hndl; } ;
struct nn_worker {int /*<<< orphan*/  timerset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_timerset_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void nn_worker_add_timer (struct nn_worker *self, int timeout,
    struct nn_worker_timer *timer)
{
    nn_timerset_add (&self->timerset, timeout, &timer->hndl);
}