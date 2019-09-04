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
struct f2fs_summary {scalar_t__ ofs_in_node; scalar_t__ version; } ;
struct f2fs_summary_block {struct f2fs_summary footer; struct f2fs_summary* entries; struct f2fs_summary journal; } ;
struct f2fs_sb_info {int blocks_per_seg; } ;
struct f2fs_checkpoint {int /*<<< orphan*/ * alloc_type; int /*<<< orphan*/ * cur_node_blkoff; int /*<<< orphan*/ * cur_node_segno; int /*<<< orphan*/ * cur_data_blkoff; int /*<<< orphan*/ * cur_data_segno; } ;
struct curseg_info {unsigned int next_segno; unsigned short next_blkoff; int /*<<< orphan*/  curseg_mutex; int /*<<< orphan*/  alloc_type; TYPE_1__* sum_blk; int /*<<< orphan*/  journal_rwsem; int /*<<< orphan*/ * journal; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_2__ {int /*<<< orphan*/  footer; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int CURSEG_HOT_DATA ; 
 int CURSEG_HOT_NODE ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 struct f2fs_checkpoint* F2FS_CKPT (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  GET_SUM_BLOCK (struct f2fs_sb_info*,unsigned int) ; 
 scalar_t__ IS_DATASEG (int) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ IS_NODESEG (int) ; 
 int /*<<< orphan*/  NR_CURSEG_DATA_TYPE ; 
 int /*<<< orphan*/  NR_CURSEG_NODE_TYPE ; 
 int /*<<< orphan*/  NR_CURSEG_TYPE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  SUM_ENTRY_SIZE ; 
 int /*<<< orphan*/  SUM_FOOTER_SIZE ; 
 int /*<<< orphan*/  SUM_JOURNAL_SIZE ; 
 scalar_t__ __exist_node_summaries (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct page* f2fs_get_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int f2fs_restore_node_summary (struct f2fs_sb_info*,unsigned int,struct f2fs_summary_block*) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct f2fs_summary*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  reset_curseg (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sum_blk_addr (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_normal_summaries(struct f2fs_sb_info *sbi, int type)
{
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(sbi);
	struct f2fs_summary_block *sum;
	struct curseg_info *curseg;
	struct page *new;
	unsigned short blk_off;
	unsigned int segno = 0;
	block_t blk_addr = 0;
	int err = 0;

	/* get segment number and block addr */
	if (IS_DATASEG(type)) {
		segno = le32_to_cpu(ckpt->cur_data_segno[type]);
		blk_off = le16_to_cpu(ckpt->cur_data_blkoff[type -
							CURSEG_HOT_DATA]);
		if (__exist_node_summaries(sbi))
			blk_addr = sum_blk_addr(sbi, NR_CURSEG_TYPE, type);
		else
			blk_addr = sum_blk_addr(sbi, NR_CURSEG_DATA_TYPE, type);
	} else {
		segno = le32_to_cpu(ckpt->cur_node_segno[type -
							CURSEG_HOT_NODE]);
		blk_off = le16_to_cpu(ckpt->cur_node_blkoff[type -
							CURSEG_HOT_NODE]);
		if (__exist_node_summaries(sbi))
			blk_addr = sum_blk_addr(sbi, NR_CURSEG_NODE_TYPE,
							type - CURSEG_HOT_NODE);
		else
			blk_addr = GET_SUM_BLOCK(sbi, segno);
	}

	new = f2fs_get_meta_page(sbi, blk_addr);
	if (IS_ERR(new))
		return PTR_ERR(new);
	sum = (struct f2fs_summary_block *)page_address(new);

	if (IS_NODESEG(type)) {
		if (__exist_node_summaries(sbi)) {
			struct f2fs_summary *ns = &sum->entries[0];
			int i;
			for (i = 0; i < sbi->blocks_per_seg; i++, ns++) {
				ns->version = 0;
				ns->ofs_in_node = 0;
			}
		} else {
			err = f2fs_restore_node_summary(sbi, segno, sum);
			if (err)
				goto out;
		}
	}

	/* set uncompleted segment to curseg */
	curseg = CURSEG_I(sbi, type);
	mutex_lock(&curseg->curseg_mutex);

	/* update journal info */
	down_write(&curseg->journal_rwsem);
	memcpy(curseg->journal, &sum->journal, SUM_JOURNAL_SIZE);
	up_write(&curseg->journal_rwsem);

	memcpy(curseg->sum_blk->entries, sum->entries, SUM_ENTRY_SIZE);
	memcpy(&curseg->sum_blk->footer, &sum->footer, SUM_FOOTER_SIZE);
	curseg->next_segno = segno;
	reset_curseg(sbi, type, 0);
	curseg->alloc_type = ckpt->alloc_type[type];
	curseg->next_blkoff = blk_off;
	mutex_unlock(&curseg->curseg_mutex);
out:
	f2fs_put_page(new, 1);
	return err;
}