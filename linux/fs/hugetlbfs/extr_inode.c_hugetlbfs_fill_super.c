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
struct hugetlbfs_sb_info {struct hugetlbfs_sb_info* spool; int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  free_inodes; int /*<<< orphan*/  max_inodes; int /*<<< orphan*/  hstate; int /*<<< orphan*/  stat_lock; } ;
struct hugetlbfs_fs_context {int max_hpages; int min_hpages; int /*<<< orphan*/  hstate; int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  nr_inodes; } ;
struct fs_context {struct hugetlbfs_fs_context* fs_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HUGETLBFS_MAGIC ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  d_make_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_page_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_page_size (int /*<<< orphan*/ ) ; 
 struct hugetlbfs_sb_info* hugepage_new_subpool (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hugetlbfs_get_root (struct super_block*,struct hugetlbfs_fs_context*) ; 
 int /*<<< orphan*/  hugetlbfs_ops ; 
 int /*<<< orphan*/  kfree (struct hugetlbfs_sb_info*) ; 
 struct hugetlbfs_sb_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hugetlbfs_fill_super(struct super_block *sb, struct fs_context *fc)
{
	struct hugetlbfs_fs_context *ctx = fc->fs_private;
	struct hugetlbfs_sb_info *sbinfo;

	sbinfo = kmalloc(sizeof(struct hugetlbfs_sb_info), GFP_KERNEL);
	if (!sbinfo)
		return -ENOMEM;
	sb->s_fs_info = sbinfo;
	spin_lock_init(&sbinfo->stat_lock);
	sbinfo->hstate		= ctx->hstate;
	sbinfo->max_inodes	= ctx->nr_inodes;
	sbinfo->free_inodes	= ctx->nr_inodes;
	sbinfo->spool		= NULL;
	sbinfo->uid		= ctx->uid;
	sbinfo->gid		= ctx->gid;
	sbinfo->mode		= ctx->mode;

	/*
	 * Allocate and initialize subpool if maximum or minimum size is
	 * specified.  Any needed reservations (for minimim size) are taken
	 * taken when the subpool is created.
	 */
	if (ctx->max_hpages != -1 || ctx->min_hpages != -1) {
		sbinfo->spool = hugepage_new_subpool(ctx->hstate,
						     ctx->max_hpages,
						     ctx->min_hpages);
		if (!sbinfo->spool)
			goto out_free;
	}
	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_blocksize = huge_page_size(ctx->hstate);
	sb->s_blocksize_bits = huge_page_shift(ctx->hstate);
	sb->s_magic = HUGETLBFS_MAGIC;
	sb->s_op = &hugetlbfs_ops;
	sb->s_time_gran = 1;
	sb->s_root = d_make_root(hugetlbfs_get_root(sb, ctx));
	if (!sb->s_root)
		goto out_free;
	return 0;
out_free:
	kfree(sbinfo->spool);
	kfree(sbinfo);
	return -ENOMEM;
}