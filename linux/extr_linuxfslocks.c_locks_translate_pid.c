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
struct pid_namespace {int dummy; } ;
struct pid {int dummy; } ;
struct file_lock {int fl_pid; } ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ IS_OFDLCK (struct file_lock*) ; 
 scalar_t__ IS_REMOTELCK (struct file_lock*) ; 
 struct pid* find_pid_ns (int,struct pid_namespace*) ; 
 struct pid_namespace init_pid_ns ; 
 int pid_nr_ns (struct pid*,struct pid_namespace*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static pid_t locks_translate_pid(struct file_lock *fl, struct pid_namespace *ns)
{
	pid_t vnr;
	struct pid *pid;

	if (IS_OFDLCK(fl))
		return -1;
	if (IS_REMOTELCK(fl))
		return fl->fl_pid;
	/*
	 * If the flock owner process is dead and its pid has been already
	 * freed, the translation below won't work, but we still want to show
	 * flock owner pid number in init pidns.
	 */
	if (ns == &init_pid_ns)
		return (pid_t)fl->fl_pid;

	rcu_read_lock();
	pid = find_pid_ns(fl->fl_pid, &init_pid_ns);
	vnr = pid_nr_ns(pid, ns);
	rcu_read_unlock();
	return vnr;
}