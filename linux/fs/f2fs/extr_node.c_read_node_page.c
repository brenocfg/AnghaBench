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
struct page {int /*<<< orphan*/  index; } ;
struct node_info {scalar_t__ blk_addr; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int op_flags; scalar_t__ new_blkaddr; scalar_t__ old_blkaddr; int /*<<< orphan*/ * encrypted_page; struct page* page; int /*<<< orphan*/  op; int /*<<< orphan*/  type; struct f2fs_sb_info* sbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int EFSBADCRC ; 
 int ENOENT ; 
 struct f2fs_sb_info* F2FS_P_SB (struct page*) ; 
 int LOCKED_PAGE ; 
 int /*<<< orphan*/  NODE ; 
 scalar_t__ NULL_ADDR ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  SBI_IS_SHUTDOWN ; 
 int f2fs_get_node_info (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct node_info*) ; 
 int /*<<< orphan*/  f2fs_inode_chksum_verify (struct f2fs_sb_info*,struct page*) ; 
 int f2fs_submit_page_bio (struct f2fs_io_info*) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int read_node_page(struct page *page, int op_flags)
{
	struct f2fs_sb_info *sbi = F2FS_P_SB(page);
	struct node_info ni;
	struct f2fs_io_info fio = {
		.sbi = sbi,
		.type = NODE,
		.op = REQ_OP_READ,
		.op_flags = op_flags,
		.page = page,
		.encrypted_page = NULL,
	};
	int err;

	if (PageUptodate(page)) {
		if (!f2fs_inode_chksum_verify(sbi, page)) {
			ClearPageUptodate(page);
			return -EFSBADCRC;
		}
		return LOCKED_PAGE;
	}

	err = f2fs_get_node_info(sbi, page->index, &ni);
	if (err)
		return err;

	if (unlikely(ni.blk_addr == NULL_ADDR) ||
			is_sbi_flag_set(sbi, SBI_IS_SHUTDOWN)) {
		ClearPageUptodate(page);
		return -ENOENT;
	}

	fio.new_blkaddr = fio.old_blkaddr = ni.blk_addr;
	return f2fs_submit_page_bio(&fio);
}