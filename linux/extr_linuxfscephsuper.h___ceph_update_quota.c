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
typedef  void* u64 ;
struct ceph_inode_info {int /*<<< orphan*/  vfs_inode; void* i_max_files; void* i_max_bytes; } ;

/* Variables and functions */
 int __ceph_has_any_quota (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  ceph_adjust_quota_realms_count (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void __ceph_update_quota(struct ceph_inode_info *ci,
				       u64 max_bytes, u64 max_files)
{
	bool had_quota, has_quota;
	had_quota = __ceph_has_any_quota(ci);
	ci->i_max_bytes = max_bytes;
	ci->i_max_files = max_files;
	has_quota = __ceph_has_any_quota(ci);

	if (had_quota != has_quota)
		ceph_adjust_quota_realms_count(&ci->vfs_inode, has_quota);
}