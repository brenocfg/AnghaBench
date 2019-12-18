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
struct nn_backoff {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_timer_term (int /*<<< orphan*/ *) ; 

void nn_backoff_term (struct nn_backoff *self)
{
    nn_timer_term (&self->timer);
}