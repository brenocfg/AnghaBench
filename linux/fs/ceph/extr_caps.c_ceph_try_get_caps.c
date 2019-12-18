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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CEPH_CAP_FILE_CACHE ; 
 int CEPH_CAP_FILE_LAZYIO ; 
 int CEPH_CAP_FILE_RD ; 
 int CEPH_CAP_FILE_SHARED ; 
 int EAGAIN ; 
 int /*<<< orphan*/  NON_BLOCKING ; 
 int ceph_pool_perm_check (struct inode*,int) ; 
 int try_get_cap_refs (struct inode*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int ceph_try_get_caps(struct inode *inode, int need, int want,
		      bool nonblock, int *got)
{
	int ret;

	BUG_ON(need & ~CEPH_CAP_FILE_RD);
	BUG_ON(want & ~(CEPH_CAP_FILE_CACHE|CEPH_CAP_FILE_LAZYIO|CEPH_CAP_FILE_SHARED));
	ret = ceph_pool_perm_check(inode, need);
	if (ret < 0)
		return ret;

	ret = try_get_cap_refs(inode, need, want, 0,
			       (nonblock ? NON_BLOCKING : 0), got);
	return ret == -EAGAIN ? 0 : ret;
}