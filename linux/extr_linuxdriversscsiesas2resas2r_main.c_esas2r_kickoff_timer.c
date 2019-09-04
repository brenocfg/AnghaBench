#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct esas2r_adapter {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  esas2r_timer_callback ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void esas2r_kickoff_timer(struct esas2r_adapter *a)
{
	timer_setup(&a->timer, esas2r_timer_callback, 0);

	a->timer.expires = jiffies +
			   msecs_to_jiffies(100);

	add_timer(&a->timer);
}