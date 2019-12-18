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
struct page {int dummy; } ;
struct f2fs_sb_info {TYPE_1__* sb; } ;
struct f2fs_orphan_block {int /*<<< orphan*/ * ino; int /*<<< orphan*/  entry_count; } ;
typedef  scalar_t__ nid_t ;
typedef  scalar_t__ block_t ;
struct TYPE_2__ {unsigned int s_flags; int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ORPHAN_PRESENT_FLAG ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  META_CP ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  SBI_IS_RECOVERED ; 
 unsigned int SB_ACTIVE ; 
 unsigned int SB_RDONLY ; 
 int __cp_payload (struct f2fs_sb_info*) ; 
 int __start_cp_addr (struct f2fs_sb_info*) ; 
 int __start_sum_addr (struct f2fs_sb_info*) ; 
 scalar_t__ bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int f2fs_enable_quota_files (struct f2fs_sb_info*,unsigned int) ; 
 struct page* f2fs_get_meta_page (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_info (struct f2fs_sb_info*,char*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_quota_off_umount (TYPE_1__*) ; 
 int /*<<< orphan*/  f2fs_ra_meta_pages (struct f2fs_sb_info*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_set_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int recover_orphan_inode (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

int f2fs_recover_orphan_inodes(struct f2fs_sb_info *sbi)
{
	block_t start_blk, orphan_blocks, i, j;
	unsigned int s_flags = sbi->sb->s_flags;
	int err = 0;
#ifdef CONFIG_QUOTA
	int quota_enabled;
#endif

	if (!is_set_ckpt_flags(sbi, CP_ORPHAN_PRESENT_FLAG))
		return 0;

	if (bdev_read_only(sbi->sb->s_bdev)) {
		f2fs_info(sbi, "write access unavailable, skipping orphan cleanup");
		return 0;
	}

	if (s_flags & SB_RDONLY) {
		f2fs_info(sbi, "orphan cleanup on readonly fs");
		sbi->sb->s_flags &= ~SB_RDONLY;
	}

#ifdef CONFIG_QUOTA
	/* Needed for iput() to work correctly and not trash data */
	sbi->sb->s_flags |= SB_ACTIVE;

	/*
	 * Turn on quotas which were not enabled for read-only mounts if
	 * filesystem has quota feature, so that they are updated correctly.
	 */
	quota_enabled = f2fs_enable_quota_files(sbi, s_flags & SB_RDONLY);
#endif

	start_blk = __start_cp_addr(sbi) + 1 + __cp_payload(sbi);
	orphan_blocks = __start_sum_addr(sbi) - 1 - __cp_payload(sbi);

	f2fs_ra_meta_pages(sbi, start_blk, orphan_blocks, META_CP, true);

	for (i = 0; i < orphan_blocks; i++) {
		struct page *page;
		struct f2fs_orphan_block *orphan_blk;

		page = f2fs_get_meta_page(sbi, start_blk + i);
		if (IS_ERR(page)) {
			err = PTR_ERR(page);
			goto out;
		}

		orphan_blk = (struct f2fs_orphan_block *)page_address(page);
		for (j = 0; j < le32_to_cpu(orphan_blk->entry_count); j++) {
			nid_t ino = le32_to_cpu(orphan_blk->ino[j]);
			err = recover_orphan_inode(sbi, ino);
			if (err) {
				f2fs_put_page(page, 1);
				goto out;
			}
		}
		f2fs_put_page(page, 1);
	}
	/* clear Orphan Flag */
	clear_ckpt_flags(sbi, CP_ORPHAN_PRESENT_FLAG);
out:
	set_sbi_flag(sbi, SBI_IS_RECOVERED);

#ifdef CONFIG_QUOTA
	/* Turn quotas off */
	if (quota_enabled)
		f2fs_quota_off_umount(sbi->sb);
#endif
	sbi->sb->s_flags = s_flags; /* Restore SB_RDONLY status */

	return err;
}