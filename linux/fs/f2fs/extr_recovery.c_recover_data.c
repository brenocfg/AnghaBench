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
struct page {int dummy; } ;
struct list_head {int dummy; } ;
struct fsync_inode_entry {scalar_t__ last_dentry; scalar_t__ blkaddr; int /*<<< orphan*/  list; int /*<<< orphan*/  inode; } ;
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {int dummy; } ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURSEG_WARM_NODE ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ IS_INODE (struct page*) ; 
 int /*<<< orphan*/  META_POR ; 
 scalar_t__ NEXT_FREE_BLKADDR (struct f2fs_sb_info*,struct curseg_info*) ; 
 int PTR_ERR (struct page*) ; 
 int do_recover_data (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  f2fs_allocate_new_segments (struct f2fs_sb_info*) ; 
 struct page* f2fs_get_tmp_page (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_ra_meta_pages_cond (struct f2fs_sb_info*,scalar_t__) ; 
 struct fsync_inode_entry* get_fsync_inode (struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_of_node (struct page*) ; 
 int /*<<< orphan*/  is_recoverable_dnode (struct page*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ next_blkaddr_of_node (struct page*) ; 
 int recover_dentry (int /*<<< orphan*/ ,struct page*,struct list_head*) ; 
 int recover_inode (int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static int recover_data(struct f2fs_sb_info *sbi, struct list_head *inode_list,
		struct list_head *tmp_inode_list, struct list_head *dir_list)
{
	struct curseg_info *curseg;
	struct page *page = NULL;
	int err = 0;
	block_t blkaddr;

	/* get node pages in the current segment */
	curseg = CURSEG_I(sbi, CURSEG_WARM_NODE);
	blkaddr = NEXT_FREE_BLKADDR(sbi, curseg);

	while (1) {
		struct fsync_inode_entry *entry;

		if (!f2fs_is_valid_blkaddr(sbi, blkaddr, META_POR))
			break;

		f2fs_ra_meta_pages_cond(sbi, blkaddr);

		page = f2fs_get_tmp_page(sbi, blkaddr);
		if (IS_ERR(page)) {
			err = PTR_ERR(page);
			break;
		}

		if (!is_recoverable_dnode(page)) {
			f2fs_put_page(page, 1);
			break;
		}

		entry = get_fsync_inode(inode_list, ino_of_node(page));
		if (!entry)
			goto next;
		/*
		 * inode(x) | CP | inode(x) | dnode(F)
		 * In this case, we can lose the latest inode(x).
		 * So, call recover_inode for the inode update.
		 */
		if (IS_INODE(page)) {
			err = recover_inode(entry->inode, page);
			if (err) {
				f2fs_put_page(page, 1);
				break;
			}
		}
		if (entry->last_dentry == blkaddr) {
			err = recover_dentry(entry->inode, page, dir_list);
			if (err) {
				f2fs_put_page(page, 1);
				break;
			}
		}
		err = do_recover_data(sbi, entry->inode, page);
		if (err) {
			f2fs_put_page(page, 1);
			break;
		}

		if (entry->blkaddr == blkaddr)
			list_move_tail(&entry->list, tmp_inode_list);
next:
		/* check next segment */
		blkaddr = next_blkaddr_of_node(page);
		f2fs_put_page(page, 1);
	}
	if (!err)
		f2fs_allocate_new_segments(sbi);
	return err;
}