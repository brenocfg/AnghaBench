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

/* Variables and functions */
 int nn_timerset_hndl_isactive (int /*<<< orphan*/ *) ; 

int nn_worker_timer_isactive (struct nn_worker_timer *self)
{
    return nn_timerset_hndl_isactive (&self->hndl);
}