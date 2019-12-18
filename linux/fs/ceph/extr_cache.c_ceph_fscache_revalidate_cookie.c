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
struct ceph_inode_info {int /*<<< orphan*/  i_truncate_mutex; int /*<<< orphan*/  i_ceph_lock; int /*<<< orphan*/  i_rdcache_gen; int /*<<< orphan*/  i_fscache_gen; int /*<<< orphan*/  fscache; int /*<<< orphan*/  i_vino; } ;

/* Variables and functions */
 scalar_t__ cache_valid (struct ceph_inode_info*) ; 
 scalar_t__ fscache_check_consistency (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_fscache_revalidate_cookie(struct ceph_inode_info *ci)
{
	if (cache_valid(ci))
		return;

	/* resue i_truncate_mutex. There should be no pending
	 * truncate while the caller holds CEPH_CAP_FILE_RD */
	mutex_lock(&ci->i_truncate_mutex);
	if (!cache_valid(ci)) {
		if (fscache_check_consistency(ci->fscache, &ci->i_vino))
			fscache_invalidate(ci->fscache);
		spin_lock(&ci->i_ceph_lock);
		ci->i_fscache_gen = ci->i_rdcache_gen;
		spin_unlock(&ci->i_ceph_lock);
	}
	mutex_unlock(&ci->i_truncate_mutex);
}