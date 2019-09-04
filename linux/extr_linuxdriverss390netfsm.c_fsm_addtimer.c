#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {int expire_event; TYPE_2__ tl; void* event_arg; } ;
typedef  TYPE_1__ fsm_timer ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  fsm_expire_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fsm_addtimer(fsm_timer *this, int millisec, int event, void *arg)
{

#if FSM_TIMER_DEBUG
	printk(KERN_DEBUG "fsm(%s): Add timer %p %dms\n",
	       this->fi->name, this, millisec);
#endif

	timer_setup(&this->tl, fsm_expire_timer, 0);
	this->expire_event = event;
	this->event_arg = arg;
	this->tl.expires = jiffies + (millisec * HZ) / 1000;
	add_timer(&this->tl);
	return 0;
}