#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_arg; int /*<<< orphan*/  expire_event; int /*<<< orphan*/  fi; } ;
typedef  TYPE_1__ fsm_timer ;

/* Variables and functions */
 TYPE_1__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* this ; 
 int /*<<< orphan*/  tl ; 

__attribute__((used)) static void
fsm_expire_timer(struct timer_list *t)
{
	fsm_timer *this = from_timer(this, t, tl);
#if FSM_TIMER_DEBUG
	printk(KERN_DEBUG "fsm(%s): Timer %p expired\n",
	       this->fi->name, this);
#endif
	fsm_event(this->fi, this->expire_event, this->event_arg);
}