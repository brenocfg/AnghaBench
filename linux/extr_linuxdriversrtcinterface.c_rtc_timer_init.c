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
struct rtc_timer {void (* func ) (void*) ;void* private_data; scalar_t__ enabled; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  timerqueue_init (int /*<<< orphan*/ *) ; 

void rtc_timer_init(struct rtc_timer *timer, void (*f)(void *p), void *data)
{
	timerqueue_init(&timer->node);
	timer->enabled = 0;
	timer->func = f;
	timer->private_data = data;
}