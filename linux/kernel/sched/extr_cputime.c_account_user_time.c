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
struct task_struct {int /*<<< orphan*/  utime; } ;

/* Variables and functions */
 int CPUTIME_NICE ; 
 int CPUTIME_USER ; 
 int /*<<< orphan*/  account_group_user_time (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acct_account_cputime (struct task_struct*) ; 
 int /*<<< orphan*/  task_group_account_field (struct task_struct*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ task_nice (struct task_struct*) ; 

void account_user_time(struct task_struct *p, u64 cputime)
{
	int index;

	/* Add user time to process. */
	p->utime += cputime;
	account_group_user_time(p, cputime);

	index = (task_nice(p) > 0) ? CPUTIME_NICE : CPUTIME_USER;

	/* Add user time to cpustat. */
	task_group_account_field(p, index, cputime);

	/* Account for user time used */
	acct_account_cputime(p);
}