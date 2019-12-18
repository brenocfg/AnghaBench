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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_checkpoint {int /*<<< orphan*/  checksum_offset; } ;
typedef  int /*<<< orphan*/  block_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 size_t CP_CHKSUM_OFFSET ; 
 size_t CP_MIN_CHKSUM_OFFSET ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ cur_cp_crc (struct f2fs_checkpoint*) ; 
 unsigned long long cur_cp_version (struct f2fs_checkpoint*) ; 
 scalar_t__ f2fs_checkpoint_chksum (struct f2fs_sb_info*,struct f2fs_checkpoint*) ; 
 struct page* f2fs_get_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_warn (struct f2fs_sb_info*,char*,...) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static int get_checkpoint_version(struct f2fs_sb_info *sbi, block_t cp_addr,
		struct f2fs_checkpoint **cp_block, struct page **cp_page,
		unsigned long long *version)
{
	size_t crc_offset = 0;
	__u32 crc;

	*cp_page = f2fs_get_meta_page(sbi, cp_addr);
	if (IS_ERR(*cp_page))
		return PTR_ERR(*cp_page);

	*cp_block = (struct f2fs_checkpoint *)page_address(*cp_page);

	crc_offset = le32_to_cpu((*cp_block)->checksum_offset);
	if (crc_offset < CP_MIN_CHKSUM_OFFSET ||
			crc_offset > CP_CHKSUM_OFFSET) {
		f2fs_put_page(*cp_page, 1);
		f2fs_warn(sbi, "invalid crc_offset: %zu", crc_offset);
		return -EINVAL;
	}

	crc = f2fs_checkpoint_chksum(sbi, *cp_block);
	if (crc != cur_cp_crc(*cp_block)) {
		f2fs_put_page(*cp_page, 1);
		f2fs_warn(sbi, "invalid crc value");
		return -EINVAL;
	}

	*version = cur_cp_version(*cp_block);
	return 0;
}