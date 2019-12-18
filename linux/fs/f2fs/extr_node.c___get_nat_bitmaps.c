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
struct f2fs_sb_info {scalar_t__ blocks_per_seg; } ;
struct f2fs_nm_info {unsigned int nat_blocks; unsigned int nat_bits_blocks; scalar_t__ full_nat_bits; scalar_t__ empty_nat_bits; scalar_t__ nat_bits; } ;
struct f2fs_checkpoint {int dummy; } ;
typedef  scalar_t__ block_t ;
typedef  int __u64 ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 unsigned int F2FS_BLKSIZE_BITS ; 
 unsigned int F2FS_BLK_ALIGN (unsigned int) ; 
 struct f2fs_checkpoint* F2FS_CKPT (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ __start_cp_addr (struct f2fs_sb_info*) ; 
 scalar_t__ cpu_to_le64 (int) ; 
 int cur_cp_crc (struct f2fs_checkpoint*) ; 
 int cur_cp_version (struct f2fs_checkpoint*) ; 
 int /*<<< orphan*/  disable_nat_bits (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  enabled_nat_bits (struct f2fs_sb_info*,int /*<<< orphan*/ *) ; 
 struct page* f2fs_get_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_kzalloc (struct f2fs_sb_info*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_notice (struct f2fs_sb_info*,char*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static int __get_nat_bitmaps(struct f2fs_sb_info *sbi)
{
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(sbi);
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	unsigned int nat_bits_bytes = nm_i->nat_blocks / BITS_PER_BYTE;
	unsigned int i;
	__u64 cp_ver = cur_cp_version(ckpt);
	block_t nat_bits_addr;

	if (!enabled_nat_bits(sbi, NULL))
		return 0;

	nm_i->nat_bits_blocks = F2FS_BLK_ALIGN((nat_bits_bytes << 1) + 8);
	nm_i->nat_bits = f2fs_kzalloc(sbi,
			nm_i->nat_bits_blocks << F2FS_BLKSIZE_BITS, GFP_KERNEL);
	if (!nm_i->nat_bits)
		return -ENOMEM;

	nat_bits_addr = __start_cp_addr(sbi) + sbi->blocks_per_seg -
						nm_i->nat_bits_blocks;
	for (i = 0; i < nm_i->nat_bits_blocks; i++) {
		struct page *page;

		page = f2fs_get_meta_page(sbi, nat_bits_addr++);
		if (IS_ERR(page))
			return PTR_ERR(page);

		memcpy(nm_i->nat_bits + (i << F2FS_BLKSIZE_BITS),
					page_address(page), F2FS_BLKSIZE);
		f2fs_put_page(page, 1);
	}

	cp_ver |= (cur_cp_crc(ckpt) << 32);
	if (cpu_to_le64(cp_ver) != *(__le64 *)nm_i->nat_bits) {
		disable_nat_bits(sbi, true);
		return 0;
	}

	nm_i->full_nat_bits = nm_i->nat_bits + 8;
	nm_i->empty_nat_bits = nm_i->full_nat_bits + nat_bits_bytes;

	f2fs_notice(sbi, "Found nat_bits in checkpoint");
	return 0;
}