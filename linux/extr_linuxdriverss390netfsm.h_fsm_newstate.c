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
struct TYPE_3__ {int /*<<< orphan*/  wait_q; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fsm_newstate(fsm_instance *fi, int newstate)
{
	atomic_set(&fi->state,newstate);
#if FSM_DEBUG_HISTORY
	fsm_record_history(fi, newstate, -1);
#endif
#if FSM_DEBUG
	printk(KERN_DEBUG "fsm(%s): New state %s\n", fi->name,
		fi->f->state_names[newstate]);
#endif
	wake_up(&fi->wait_q);
}