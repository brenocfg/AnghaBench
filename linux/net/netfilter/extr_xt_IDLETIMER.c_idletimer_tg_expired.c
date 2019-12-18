#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct idletimer_tg {int /*<<< orphan*/  work; TYPE_2__ attr; } ;

/* Variables and functions */
 struct idletimer_tg* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct idletimer_tg* timer ; 

__attribute__((used)) static void idletimer_tg_expired(struct timer_list *t)
{
	struct idletimer_tg *timer = from_timer(timer, t, timer);

	pr_debug("timer %s expired\n", timer->attr.attr.name);

	schedule_work(&timer->work);
}