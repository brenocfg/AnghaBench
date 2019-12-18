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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct cpu_itimer {scalar_t__ expires; scalar_t__ incr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_PROF ; 
 int /*<<< orphan*/  ITIMER_VIRTUAL ; 
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int SIGPROF ; 
 int /*<<< orphan*/  __group_send_sig_info (int,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  task_tgid (struct task_struct*) ; 
 int /*<<< orphan*/  trace_itimer_expire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void check_cpu_itimer(struct task_struct *tsk, struct cpu_itimer *it,
			     u64 *expires, u64 cur_time, int signo)
{
	if (!it->expires)
		return;

	if (cur_time >= it->expires) {
		if (it->incr)
			it->expires += it->incr;
		else
			it->expires = 0;

		trace_itimer_expire(signo == SIGPROF ?
				    ITIMER_PROF : ITIMER_VIRTUAL,
				    task_tgid(tsk), cur_time);
		__group_send_sig_info(signo, SEND_SIG_PRIV, tsk);
	}

	if (it->expires && it->expires < *expires)
		*expires = it->expires;
}