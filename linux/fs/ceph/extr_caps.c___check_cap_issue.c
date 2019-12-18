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
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;
struct ceph_inode_info {TYPE_1__ vfs_inode; int /*<<< orphan*/  i_shared_gen; int /*<<< orphan*/  i_rdcache_gen; } ;
struct ceph_cap {int dummy; } ;

/* Variables and functions */
 unsigned int CEPH_CAP_FILE_CACHE ; 
 unsigned int CEPH_CAP_FILE_LAZYIO ; 
 unsigned int CEPH_CAP_FILE_SHARED ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 unsigned int __ceph_caps_issued (struct ceph_inode_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ceph_dir_clear_complete (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,TYPE_1__*) ; 

__attribute__((used)) static void __check_cap_issue(struct ceph_inode_info *ci, struct ceph_cap *cap,
			      unsigned issued)
{
	unsigned had = __ceph_caps_issued(ci, NULL);

	/*
	 * Each time we receive FILE_CACHE anew, we increment
	 * i_rdcache_gen.
	 */
	if ((issued & (CEPH_CAP_FILE_CACHE|CEPH_CAP_FILE_LAZYIO)) &&
	    (had & (CEPH_CAP_FILE_CACHE|CEPH_CAP_FILE_LAZYIO)) == 0) {
		ci->i_rdcache_gen++;
	}

	/*
	 * If FILE_SHARED is newly issued, mark dir not complete. We don't
	 * know what happened to this directory while we didn't have the cap.
	 * If FILE_SHARED is being revoked, also mark dir not complete. It
	 * stops on-going cached readdir.
	 */
	if ((issued & CEPH_CAP_FILE_SHARED) != (had & CEPH_CAP_FILE_SHARED)) {
		if (issued & CEPH_CAP_FILE_SHARED)
			atomic_inc(&ci->i_shared_gen);
		if (S_ISDIR(ci->vfs_inode.i_mode)) {
			dout(" marking %p NOT complete\n", &ci->vfs_inode);
			__ceph_dir_clear_complete(ci);
		}
	}
}