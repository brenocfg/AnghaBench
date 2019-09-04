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
struct afs_cell {scalar_t__ dns_expiry; int error; int /*<<< orphan*/  vl_addrs_lock; int /*<<< orphan*/  vl_addrs; int /*<<< orphan*/  flags; } ;
struct afs_addr_list {scalar_t__ nr_addrs; int /*<<< orphan*/  index; } ;
struct afs_addr_cursor {int begun; scalar_t__ error; int /*<<< orphan*/  start; int /*<<< orphan*/  index; int /*<<< orphan*/ * addr; struct afs_addr_list* alist; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CELL_FL_NO_LOOKUP_YET ; 
 int EDESTADDRREQ ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  afs_get_addrlist (struct afs_addr_list*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct afs_addr_list* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int afs_set_vl_cursor(struct afs_addr_cursor *ac, struct afs_cell *cell)
{
	struct afs_addr_list *alist;
	int ret;

	if (!rcu_access_pointer(cell->vl_addrs)) {
		ret = wait_on_bit(&cell->flags, AFS_CELL_FL_NO_LOOKUP_YET,
				  TASK_INTERRUPTIBLE);
		if (ret < 0)
			return ret;

		if (!rcu_access_pointer(cell->vl_addrs) &&
		    ktime_get_real_seconds() < cell->dns_expiry)
			return cell->error;
	}

	read_lock(&cell->vl_addrs_lock);
	alist = rcu_dereference_protected(cell->vl_addrs,
					  lockdep_is_held(&cell->vl_addrs_lock));
	if (alist->nr_addrs > 0)
		afs_get_addrlist(alist);
	else
		alist = NULL;
	read_unlock(&cell->vl_addrs_lock);

	if (!alist)
		return -EDESTADDRREQ;

	ac->alist = alist;
	ac->addr = NULL;
	ac->start = READ_ONCE(alist->index);
	ac->index = ac->start;
	ac->error = 0;
	ac->begun = false;
	return 0;
}