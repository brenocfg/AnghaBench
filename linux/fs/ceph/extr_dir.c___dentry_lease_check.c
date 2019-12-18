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
struct dentry {int dummy; } ;
struct ceph_dentry_info {int dummy; } ;

/* Variables and functions */
 int DELETE ; 
 int EBUSY ; 
 int KEEP ; 
 int STOP ; 
 int TOUCH ; 
 scalar_t__ __dentry_lease_is_valid (struct ceph_dentry_info*) ; 
 int __dir_lease_try_check (struct dentry*) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 

__attribute__((used)) static int __dentry_lease_check(struct dentry *dentry, void *arg)
{
	struct ceph_dentry_info *di = ceph_dentry(dentry);
	int ret;

	if (__dentry_lease_is_valid(di))
		return STOP;
	ret = __dir_lease_try_check(dentry);
	if (ret == -EBUSY)
		return KEEP;
	if (ret > 0)
		return TOUCH;
	return DELETE;
}