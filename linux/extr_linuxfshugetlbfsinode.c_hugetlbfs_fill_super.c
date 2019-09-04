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
struct super_block {int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; struct hugetlbfs_sb_info* s_fs_info; } ;
struct hugetlbfs_sb_info {int max_inodes; int free_inodes; int mode; struct hugetlbfs_sb_info* spool; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  stat_lock; int /*<<< orphan*/ * hstate; } ;
struct hugetlbfs_config {int max_hpages; int nr_inodes; int mode; int min_hpages; int /*<<< orphan*/ * hstate; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HUGETLBFS_MAGIC ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  d_make_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_hstate ; 
 int /*<<< orphan*/  huge_page_shift (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_page_size (int /*<<< orphan*/ *) ; 
 struct hugetlbfs_sb_info* hugepage_new_subpool (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hugetlbfs_get_root (struct super_block*,struct hugetlbfs_config*) ; 
 int /*<<< orphan*/  hugetlbfs_ops ; 
 int hugetlbfs_parse_options (void*,struct hugetlbfs_config*) ; 
 int /*<<< orphan*/  kfree (struct hugetlbfs_sb_info*) ; 
 struct hugetlbfs_sb_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hugetlbfs_fill_super(struct super_block *sb, void *data, int silent)
{
	int ret;
	struct hugetlbfs_config config;
	struct hugetlbfs_sb_info *sbinfo;

	config.max_hpages = -1; /* No limit on size by default */
	config.nr_inodes = -1; /* No limit on number of inodes by default */
	config.uid = current_fsuid();
	config.gid = current_fsgid();
	config.mode = 0755;
	config.hstate = &default_hstate;
	config.min_hpages = -1; /* No default minimum size */
	ret = hugetlbfs_parse_options(data, &config);
	if (ret)
		return ret;

	sbinfo = kmalloc(sizeof(struct hugetlbfs_sb_info), GFP_KERNEL);
	if (!sbinfo)
		return -ENOMEM;
	sb->s_fs_info = sbinfo;
	sbinfo->hstate = config.hstate;
	spin_lock_init(&sbinfo->stat_lock);
	sbinfo->max_inodes = config.nr_inodes;
	sbinfo->free_inodes = config.nr_inodes;
	sbinfo->spool = NULL;
	sbinfo->uid = config.uid;
	sbinfo->gid = config.gid;
	sbinfo->mode = config.mode;

	/*
	 * Allocate and initialize subpool if maximum or minimum size is
	 * specified.  Any needed reservations (for minimim size) are taken
	 * taken when the subpool is created.
	 */
	if (config.max_hpages != -1 || config.min_hpages != -1) {
		sbinfo->spool = hugepage_new_subpool(config.hstate,
							config.max_hpages,
							config.min_hpages);
		if (!sbinfo->spool)
			goto out_free;
	}
	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_blocksize = huge_page_size(config.hstate);
	sb->s_blocksize_bits = huge_page_shift(config.hstate);
	sb->s_magic = HUGETLBFS_MAGIC;
	sb->s_op = &hugetlbfs_ops;
	sb->s_time_gran = 1;
	sb->s_root = d_make_root(hugetlbfs_get_root(sb, &config));
	if (!sb->s_root)
		goto out_free;
	return 0;
out_free:
	kfree(sbinfo->spool);
	kfree(sbinfo);
	return -ENOMEM;
}