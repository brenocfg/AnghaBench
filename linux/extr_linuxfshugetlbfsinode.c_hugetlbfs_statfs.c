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
struct kstatfs {long f_blocks; long f_bavail; long f_bfree; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct hugetlbfs_sb_info {int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  free_inodes; int /*<<< orphan*/  max_inodes; TYPE_1__* spool; } ;
struct hstate {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {long max_hpages; long used_hpages; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUGETLBFS_MAGIC ; 
 struct hugetlbfs_sb_info* HUGETLBFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct hstate* hstate_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hugetlbfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(dentry->d_sb);
	struct hstate *h = hstate_inode(d_inode(dentry));

	buf->f_type = HUGETLBFS_MAGIC;
	buf->f_bsize = huge_page_size(h);
	if (sbinfo) {
		spin_lock(&sbinfo->stat_lock);
		/* If no limits set, just report 0 for max/free/used
		 * blocks, like simple_statfs() */
		if (sbinfo->spool) {
			long free_pages;

			spin_lock(&sbinfo->spool->lock);
			buf->f_blocks = sbinfo->spool->max_hpages;
			free_pages = sbinfo->spool->max_hpages
				- sbinfo->spool->used_hpages;
			buf->f_bavail = buf->f_bfree = free_pages;
			spin_unlock(&sbinfo->spool->lock);
			buf->f_files = sbinfo->max_inodes;
			buf->f_ffree = sbinfo->free_inodes;
		}
		spin_unlock(&sbinfo->stat_lock);
	}
	buf->f_namelen = NAME_MAX;
	return 0;
}