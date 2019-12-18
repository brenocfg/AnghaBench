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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int /*<<< orphan*/  stime; } ;
typedef  enum cpu_usage_stat { ____Placeholder_cpu_usage_stat } cpu_usage_stat ;

/* Variables and functions */
 int /*<<< orphan*/  account_group_system_time (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acct_account_cputime (struct task_struct*) ; 
 int /*<<< orphan*/  task_group_account_field (struct task_struct*,int,int /*<<< orphan*/ ) ; 

void account_system_index_time(struct task_struct *p,
			       u64 cputime, enum cpu_usage_stat index)
{
	/* Add system time to process. */
	p->stime += cputime;
	account_group_system_time(p, cputime);

	/* Add system time to cpustat. */
	task_group_account_field(p, index, cputime);

	/* Account for system time used */
	acct_account_cputime(p);
}