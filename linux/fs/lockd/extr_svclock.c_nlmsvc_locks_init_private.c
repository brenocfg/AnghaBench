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
struct nlm_host {int dummy; } ;
struct file_lock {int /*<<< orphan*/ * fl_ops; int /*<<< orphan*/ * fl_owner; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/ * nlmsvc_find_lockowner (struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsvc_lock_ops ; 

void nlmsvc_locks_init_private(struct file_lock *fl, struct nlm_host *host,
						pid_t pid)
{
	fl->fl_owner = nlmsvc_find_lockowner(host, pid);
	if (fl->fl_owner != NULL)
		fl->fl_ops = &nlmsvc_lock_ops;
}