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
struct nlm_host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  owner; scalar_t__ state; } ;
struct TYPE_4__ {TYPE_1__ nfs_fl; } ;
struct file_lock {int /*<<< orphan*/ * fl_ops; TYPE_2__ fl_u; int /*<<< orphan*/  fl_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmclnt_find_lockowner (struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmclnt_lock_ops ; 

__attribute__((used)) static void nlmclnt_locks_init_private(struct file_lock *fl, struct nlm_host *host)
{
	fl->fl_u.nfs_fl.state = 0;
	fl->fl_u.nfs_fl.owner = nlmclnt_find_lockowner(host, fl->fl_owner);
	INIT_LIST_HEAD(&fl->fl_u.nfs_fl.list);
	fl->fl_ops = &nlmclnt_lock_ops;
}