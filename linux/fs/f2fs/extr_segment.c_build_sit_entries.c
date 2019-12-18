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
struct sit_info {unsigned int sents_per_block; struct seg_entry* sentries; } ;
struct seg_entry {unsigned int valid_blocks; int /*<<< orphan*/  cur_valid_map; int /*<<< orphan*/  discard_map; int /*<<< orphan*/  type; } ;
struct page {int dummy; } ;
struct f2fs_sit_entry {int dummy; } ;
struct f2fs_sit_block {struct f2fs_sit_entry* entries; } ;
struct f2fs_sb_info {unsigned int discard_blks; unsigned int blocks_per_seg; } ;
struct f2fs_journal {int dummy; } ;
struct curseg_info {int /*<<< orphan*/  journal_rwsem; struct f2fs_journal* journal; } ;
typedef  unsigned int block_t ;
struct TYPE_2__ {unsigned int valid_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  CP_TRIMMED_FLAG ; 
 int /*<<< orphan*/  CURSEG_COLD_DATA ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int EFSCORRUPTED ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ IS_NODESEG (int /*<<< orphan*/ ) ; 
 unsigned int MAIN_SEGS (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  META_SIT ; 
 int PTR_ERR (struct page*) ; 
 int SIT_BLK_CNT (struct f2fs_sb_info*) ; 
 size_t SIT_ENTRY_OFFSET (struct sit_info*,unsigned int) ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  SIT_VBLOCK_MAP_SIZE ; 
 scalar_t__ __is_large_section (struct f2fs_sb_info*) ; 
 int check_block_count (struct f2fs_sb_info*,unsigned int,struct f2fs_sit_entry*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_err (struct f2fs_sb_info*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 unsigned int f2fs_ra_meta_pages (struct f2fs_sb_info*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct page* get_current_sit_page (struct f2fs_sb_info*,unsigned int) ; 
 TYPE_1__* get_sec_entry (struct f2fs_sb_info*,unsigned int) ; 
 scalar_t__ is_set_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  seg_info_from_raw_sit (struct seg_entry*,struct f2fs_sit_entry*) ; 
 int /*<<< orphan*/  segno_in_journal (struct f2fs_journal*,unsigned int) ; 
 struct f2fs_sit_entry sit_in_journal (struct f2fs_journal*,unsigned int) ; 
 unsigned int sits_in_cursum (struct f2fs_journal*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 unsigned int valid_node_count (struct f2fs_sb_info*) ; 

__attribute__((used)) static int build_sit_entries(struct f2fs_sb_info *sbi)
{
	struct sit_info *sit_i = SIT_I(sbi);
	struct curseg_info *curseg = CURSEG_I(sbi, CURSEG_COLD_DATA);
	struct f2fs_journal *journal = curseg->journal;
	struct seg_entry *se;
	struct f2fs_sit_entry sit;
	int sit_blk_cnt = SIT_BLK_CNT(sbi);
	unsigned int i, start, end;
	unsigned int readed, start_blk = 0;
	int err = 0;
	block_t total_node_blocks = 0;

	do {
		readed = f2fs_ra_meta_pages(sbi, start_blk, BIO_MAX_PAGES,
							META_SIT, true);

		start = start_blk * sit_i->sents_per_block;
		end = (start_blk + readed) * sit_i->sents_per_block;

		for (; start < end && start < MAIN_SEGS(sbi); start++) {
			struct f2fs_sit_block *sit_blk;
			struct page *page;

			se = &sit_i->sentries[start];
			page = get_current_sit_page(sbi, start);
			if (IS_ERR(page))
				return PTR_ERR(page);
			sit_blk = (struct f2fs_sit_block *)page_address(page);
			sit = sit_blk->entries[SIT_ENTRY_OFFSET(sit_i, start)];
			f2fs_put_page(page, 1);

			err = check_block_count(sbi, start, &sit);
			if (err)
				return err;
			seg_info_from_raw_sit(se, &sit);
			if (IS_NODESEG(se->type))
				total_node_blocks += se->valid_blocks;

			/* build discard map only one time */
			if (is_set_ckpt_flags(sbi, CP_TRIMMED_FLAG)) {
				memset(se->discard_map, 0xff,
					SIT_VBLOCK_MAP_SIZE);
			} else {
				memcpy(se->discard_map,
					se->cur_valid_map,
					SIT_VBLOCK_MAP_SIZE);
				sbi->discard_blks +=
					sbi->blocks_per_seg -
					se->valid_blocks;
			}

			if (__is_large_section(sbi))
				get_sec_entry(sbi, start)->valid_blocks +=
							se->valid_blocks;
		}
		start_blk += readed;
	} while (start_blk < sit_blk_cnt);

	down_read(&curseg->journal_rwsem);
	for (i = 0; i < sits_in_cursum(journal); i++) {
		unsigned int old_valid_blocks;

		start = le32_to_cpu(segno_in_journal(journal, i));
		if (start >= MAIN_SEGS(sbi)) {
			f2fs_err(sbi, "Wrong journal entry on segno %u",
				 start);
			err = -EFSCORRUPTED;
			break;
		}

		se = &sit_i->sentries[start];
		sit = sit_in_journal(journal, i);

		old_valid_blocks = se->valid_blocks;
		if (IS_NODESEG(se->type))
			total_node_blocks -= old_valid_blocks;

		err = check_block_count(sbi, start, &sit);
		if (err)
			break;
		seg_info_from_raw_sit(se, &sit);
		if (IS_NODESEG(se->type))
			total_node_blocks += se->valid_blocks;

		if (is_set_ckpt_flags(sbi, CP_TRIMMED_FLAG)) {
			memset(se->discard_map, 0xff, SIT_VBLOCK_MAP_SIZE);
		} else {
			memcpy(se->discard_map, se->cur_valid_map,
						SIT_VBLOCK_MAP_SIZE);
			sbi->discard_blks += old_valid_blocks;
			sbi->discard_blks -= se->valid_blocks;
		}

		if (__is_large_section(sbi)) {
			get_sec_entry(sbi, start)->valid_blocks +=
							se->valid_blocks;
			get_sec_entry(sbi, start)->valid_blocks -=
							old_valid_blocks;
		}
	}
	up_read(&curseg->journal_rwsem);

	if (!err && total_node_blocks != valid_node_count(sbi)) {
		f2fs_err(sbi, "SIT is corrupted node# %u vs %u",
			 total_node_blocks, valid_node_count(sbi));
		err = -EFSCORRUPTED;
	}

	return err;
}