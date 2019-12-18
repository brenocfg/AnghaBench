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
struct task_struct {int dummy; } ;
struct TYPE_4__ {struct task_struct* p; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 scalar_t__ KDB_TSK (int) ; 
 int _TIF_MCA_INIT ; 
 struct task_struct* curr_task (int) ; 
 TYPE_2__* krp ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 

struct task_struct *kdb_curr_task(int cpu)
{
	struct task_struct *p = curr_task(cpu);
#ifdef	_TIF_MCA_INIT
	if ((task_thread_info(p)->flags & _TIF_MCA_INIT) && KDB_TSK(cpu))
		p = krp->p;
#endif
	return p;
}