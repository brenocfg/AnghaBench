#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ count; } ;
struct dentry {TYPE_1__ d_lockref; } ;
struct ceph_lease_walk_control {int /*<<< orphan*/  expire_dir_lease; scalar_t__ dir_lease_ttl; } ;
struct ceph_dentry_info {int flags; scalar_t__ lease_shared_gen; scalar_t__ time; } ;

/* Variables and functions */
 int CEPH_DENTRY_REFERENCED ; 
 int DELETE ; 
 int EBUSY ; 
 int KEEP ; 
 int STOP ; 
 int TOUCH ; 
 int __dir_lease_try_check (struct dentry*) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __dir_lease_check(struct dentry *dentry, void *arg)
{
	struct ceph_lease_walk_control *lwc = arg;
	struct ceph_dentry_info *di = ceph_dentry(dentry);

	int ret = __dir_lease_try_check(dentry);
	if (ret == -EBUSY)
		return KEEP;
	if (ret > 0) {
		if (time_before(jiffies, di->time + lwc->dir_lease_ttl))
			return STOP;
		/* Move dentry to tail of dir lease list if we don't want
		 * to delete it. So dentries in the list are checked in a
		 * round robin manner */
		if (!lwc->expire_dir_lease)
			return TOUCH;
		if (dentry->d_lockref.count > 0 ||
		    (di->flags & CEPH_DENTRY_REFERENCED))
			return TOUCH;
		/* invalidate dir lease */
		di->lease_shared_gen = 0;
	}
	return DELETE;
}