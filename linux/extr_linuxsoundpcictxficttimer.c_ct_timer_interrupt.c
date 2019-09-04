#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ct_timer {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* interrupt ) (struct ct_timer*) ;} ;

/* Variables and functions */
 unsigned int IT_INT ; 
 int /*<<< orphan*/  stub1 (struct ct_timer*) ; 

__attribute__((used)) static void ct_timer_interrupt(void *data, unsigned int status)
{
	struct ct_timer *timer = data;

	/* Interval timer interrupt */
	if ((status & IT_INT) && timer->ops->interrupt)
		timer->ops->interrupt(timer);
}