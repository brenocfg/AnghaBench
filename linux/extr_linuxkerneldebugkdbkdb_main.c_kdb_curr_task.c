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
struct task_struct {int dummy; } ;

/* Variables and functions */
 struct task_struct* curr_task (int) ; 

struct task_struct *kdb_curr_task(int cpu)
{
	struct task_struct *p = curr_task(cpu);
#ifdef	_TIF_MCA_INIT
	if ((task_thread_info(p)->flags & _TIF_MCA_INIT) && KDB_TSK(cpu))
		p = krp->p;
#endif
	return p;
}