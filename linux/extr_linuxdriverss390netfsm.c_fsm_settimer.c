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
struct TYPE_3__ {int /*<<< orphan*/  tl; int /*<<< orphan*/ * fi; } ;
typedef  TYPE_1__ fsm_timer ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  fsm_expire_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fsm_settimer(fsm_instance *fi, fsm_timer *this)
{
	this->fi = fi;
#if FSM_TIMER_DEBUG
	printk(KERN_DEBUG "fsm(%s): Create timer %p\n", fi->name,
	       this);
#endif
	timer_setup(&this->tl, fsm_expire_timer, 0);
}