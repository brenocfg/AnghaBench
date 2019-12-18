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
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  DATA ; 
 int EFAULT ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  F2FS_RD_DATA ; 
 scalar_t__ IS_ERR (struct bio*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct bio*) ; 
 int /*<<< orphan*/  __submit_bio (struct f2fs_sb_info*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_add_page (struct bio*,struct page*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 struct bio* f2fs_grab_read_bio (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_block_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_page_count (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_submit_page_read(struct inode *inode, struct page *page,
							block_t blkaddr)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct bio *bio;

	bio = f2fs_grab_read_bio(inode, blkaddr, 1, 0, page->index);
	if (IS_ERR(bio))
		return PTR_ERR(bio);

	/* wait for GCed page writeback via META_MAPPING */
	f2fs_wait_on_block_writeback(inode, blkaddr);

	if (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) {
		bio_put(bio);
		return -EFAULT;
	}
	ClearPageError(page);
	inc_page_count(sbi, F2FS_RD_DATA);
	__submit_bio(sbi, bio, DATA);
	return 0;
}