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
struct f2fs_sb_info {unsigned long blocksize; int /*<<< orphan*/  sb; } ;
struct f2fs_checkpoint {int /*<<< orphan*/  checksum_offset; } ;
typedef  int /*<<< orphan*/  block_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  cur_cp_crc (struct f2fs_checkpoint*) ; 
 unsigned long long cur_cp_version (struct f2fs_checkpoint*) ; 
 int /*<<< orphan*/  f2fs_crc_valid (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct f2fs_checkpoint*,size_t) ; 
 struct page* f2fs_get_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static int get_checkpoint_version(struct f2fs_sb_info *sbi, block_t cp_addr,
		struct f2fs_checkpoint **cp_block, struct page **cp_page,
		unsigned long long *version)
{
	unsigned long blk_size = sbi->blocksize;
	size_t crc_offset = 0;
	__u32 crc = 0;

	*cp_page = f2fs_get_meta_page(sbi, cp_addr);
	if (IS_ERR(*cp_page))
		return PTR_ERR(*cp_page);

	*cp_block = (struct f2fs_checkpoint *)page_address(*cp_page);

	crc_offset = le32_to_cpu((*cp_block)->checksum_offset);
	if (crc_offset > (blk_size - sizeof(__le32))) {
		f2fs_put_page(*cp_page, 1);
		f2fs_msg(sbi->sb, KERN_WARNING,
			"invalid crc_offset: %zu", crc_offset);
		return -EINVAL;
	}

	crc = cur_cp_crc(*cp_block);
	if (!f2fs_crc_valid(sbi, crc, *cp_block, crc_offset)) {
		f2fs_put_page(*cp_page, 1);
		f2fs_msg(sbi->sb, KERN_WARNING, "invalid crc value");
		return -EINVAL;
	}

	*version = cur_cp_version(*cp_block);
	return 0;
}