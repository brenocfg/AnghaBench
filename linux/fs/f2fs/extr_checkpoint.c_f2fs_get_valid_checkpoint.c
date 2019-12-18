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
struct f2fs_super_block {int /*<<< orphan*/  log_blocks_per_seg; int /*<<< orphan*/  cp_blkaddr; } ;
struct f2fs_sb_info {unsigned long blocksize; unsigned char* ckpt; int cur_cp_pack; struct f2fs_super_block* raw_super; } ;
typedef  void f2fs_checkpoint ;
typedef  int block_t ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int __cp_payload (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  array_size (unsigned long,unsigned int) ; 
 struct page* f2fs_get_meta_page (struct f2fs_sb_info*,int) ; 
 unsigned char* f2fs_kzalloc (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 scalar_t__ f2fs_sanity_check_ckpt (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  kvfree (unsigned char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,unsigned long) ; 
 void* page_address (struct page*) ; 
 struct page* validate_checkpoint (struct f2fs_sb_info*,unsigned long long,unsigned long long*) ; 
 scalar_t__ ver_after (unsigned long long,unsigned long long) ; 

int f2fs_get_valid_checkpoint(struct f2fs_sb_info *sbi)
{
	struct f2fs_checkpoint *cp_block;
	struct f2fs_super_block *fsb = sbi->raw_super;
	struct page *cp1, *cp2, *cur_page;
	unsigned long blk_size = sbi->blocksize;
	unsigned long long cp1_version = 0, cp2_version = 0;
	unsigned long long cp_start_blk_no;
	unsigned int cp_blks = 1 + __cp_payload(sbi);
	block_t cp_blk_no;
	int i;
	int err;

	sbi->ckpt = f2fs_kzalloc(sbi, array_size(blk_size, cp_blks),
				 GFP_KERNEL);
	if (!sbi->ckpt)
		return -ENOMEM;
	/*
	 * Finding out valid cp block involves read both
	 * sets( cp pack1 and cp pack 2)
	 */
	cp_start_blk_no = le32_to_cpu(fsb->cp_blkaddr);
	cp1 = validate_checkpoint(sbi, cp_start_blk_no, &cp1_version);

	/* The second checkpoint pack should start at the next segment */
	cp_start_blk_no += ((unsigned long long)1) <<
				le32_to_cpu(fsb->log_blocks_per_seg);
	cp2 = validate_checkpoint(sbi, cp_start_blk_no, &cp2_version);

	if (cp1 && cp2) {
		if (ver_after(cp2_version, cp1_version))
			cur_page = cp2;
		else
			cur_page = cp1;
	} else if (cp1) {
		cur_page = cp1;
	} else if (cp2) {
		cur_page = cp2;
	} else {
		err = -EFSCORRUPTED;
		goto fail_no_cp;
	}

	cp_block = (struct f2fs_checkpoint *)page_address(cur_page);
	memcpy(sbi->ckpt, cp_block, blk_size);

	if (cur_page == cp1)
		sbi->cur_cp_pack = 1;
	else
		sbi->cur_cp_pack = 2;

	/* Sanity checking of checkpoint */
	if (f2fs_sanity_check_ckpt(sbi)) {
		err = -EFSCORRUPTED;
		goto free_fail_no_cp;
	}

	if (cp_blks <= 1)
		goto done;

	cp_blk_no = le32_to_cpu(fsb->cp_blkaddr);
	if (cur_page == cp2)
		cp_blk_no += 1 << le32_to_cpu(fsb->log_blocks_per_seg);

	for (i = 1; i < cp_blks; i++) {
		void *sit_bitmap_ptr;
		unsigned char *ckpt = (unsigned char *)sbi->ckpt;

		cur_page = f2fs_get_meta_page(sbi, cp_blk_no + i);
		if (IS_ERR(cur_page)) {
			err = PTR_ERR(cur_page);
			goto free_fail_no_cp;
		}
		sit_bitmap_ptr = page_address(cur_page);
		memcpy(ckpt + i * blk_size, sit_bitmap_ptr, blk_size);
		f2fs_put_page(cur_page, 1);
	}
done:
	f2fs_put_page(cp1, 1);
	f2fs_put_page(cp2, 1);
	return 0;

free_fail_no_cp:
	f2fs_put_page(cp1, 1);
	f2fs_put_page(cp2, 1);
fail_no_cp:
	kvfree(sbi->ckpt);
	return err;
}