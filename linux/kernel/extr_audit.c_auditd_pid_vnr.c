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
struct auditd_connection {int /*<<< orphan*/  pid; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  auditd_conn ; 
 scalar_t__ pid_vnr (int /*<<< orphan*/ ) ; 
 struct auditd_connection* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static pid_t auditd_pid_vnr(void)
{
	pid_t pid;
	const struct auditd_connection *ac;

	rcu_read_lock();
	ac = rcu_dereference(auditd_conn);
	if (!ac || !ac->pid)
		pid = 0;
	else
		pid = pid_vnr(ac->pid);
	rcu_read_unlock();

	return pid;
}