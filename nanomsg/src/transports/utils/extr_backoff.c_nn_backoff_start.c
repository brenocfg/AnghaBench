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
struct nn_backoff {int n; int minivl; int maxivl; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_timer_start (int /*<<< orphan*/ *,int) ; 

void nn_backoff_start (struct nn_backoff *self)
{
     int timeout;

     /*  Start the timer for the actual n value. If the interval haven't yet
         exceeded the maximum, double the next timeout value. */
     timeout = (self->n - 1) * self->minivl;
     if (timeout > self->maxivl)
         timeout = self->maxivl;
     else
         self->n *= 2;
     nn_timer_start (&self->timer, timeout);
}