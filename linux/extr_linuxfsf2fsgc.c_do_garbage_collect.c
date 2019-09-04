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
struct gc_inode_list {int dummy; } ;
struct f2fs_summary_block {int /*<<< orphan*/  entries; int /*<<< orphan*/  footer; } ;
struct f2fs_sb_info {int segs_per_sec; int /*<<< orphan*/  stat_info; int /*<<< orphan*/  sb; } ;
struct blk_plug {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int FG_GC ; 
 int /*<<< orphan*/  GET_SUM_BLOCK (struct f2fs_sb_info*,unsigned int) ; 
 unsigned char GET_SUM_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_DATASEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  META_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  META_SSA ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 unsigned char SUM_TYPE_DATA ; 
 unsigned char SUM_TYPE_NODE ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 struct page* f2fs_get_sum_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_ra_meta_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_data_segment (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct gc_inode_list*,unsigned int,int) ; 
 int /*<<< orphan*/  gc_node_segment (struct f2fs_sb_info*,int /*<<< orphan*/ ,unsigned int,int) ; 
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 scalar_t__ get_valid_blocks (struct f2fs_sb_info*,unsigned int,int) ; 
 struct f2fs_summary_block* page_address (struct page*) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_inc_call_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_inc_seg_count (struct f2fs_sb_info*,unsigned char,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int do_garbage_collect(struct f2fs_sb_info *sbi,
				unsigned int start_segno,
				struct gc_inode_list *gc_list, int gc_type)
{
	struct page *sum_page;
	struct f2fs_summary_block *sum;
	struct blk_plug plug;
	unsigned int segno = start_segno;
	unsigned int end_segno = start_segno + sbi->segs_per_sec;
	int seg_freed = 0;
	unsigned char type = IS_DATASEG(get_seg_entry(sbi, segno)->type) ?
						SUM_TYPE_DATA : SUM_TYPE_NODE;

	/* readahead multi ssa blocks those have contiguous address */
	if (sbi->segs_per_sec > 1)
		f2fs_ra_meta_pages(sbi, GET_SUM_BLOCK(sbi, segno),
					sbi->segs_per_sec, META_SSA, true);

	/* reference all summary page */
	while (segno < end_segno) {
		sum_page = f2fs_get_sum_page(sbi, segno++);
		unlock_page(sum_page);
	}

	blk_start_plug(&plug);

	for (segno = start_segno; segno < end_segno; segno++) {

		/* find segment summary of victim */
		sum_page = find_get_page(META_MAPPING(sbi),
					GET_SUM_BLOCK(sbi, segno));
		f2fs_put_page(sum_page, 0);

		if (get_valid_blocks(sbi, segno, false) == 0 ||
				!PageUptodate(sum_page) ||
				unlikely(f2fs_cp_error(sbi)))
			goto next;

		sum = page_address(sum_page);
		if (type != GET_SUM_TYPE((&sum->footer))) {
			f2fs_msg(sbi->sb, KERN_ERR, "Inconsistent segment (%u) "
				"type [%d, %d] in SSA and SIT",
				segno, type, GET_SUM_TYPE((&sum->footer)));
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			goto next;
		}

		/*
		 * this is to avoid deadlock:
		 * - lock_page(sum_page)         - f2fs_replace_block
		 *  - check_valid_map()            - down_write(sentry_lock)
		 *   - down_read(sentry_lock)     - change_curseg()
		 *                                  - lock_page(sum_page)
		 */
		if (type == SUM_TYPE_NODE)
			gc_node_segment(sbi, sum->entries, segno, gc_type);
		else
			gc_data_segment(sbi, sum->entries, gc_list, segno,
								gc_type);

		stat_inc_seg_count(sbi, type, gc_type);

		if (gc_type == FG_GC &&
				get_valid_blocks(sbi, segno, false) == 0)
			seg_freed++;
next:
		f2fs_put_page(sum_page, 0);
	}

	if (gc_type == FG_GC)
		f2fs_submit_merged_write(sbi,
				(type == SUM_TYPE_NODE) ? NODE : DATA);

	blk_finish_plug(&plug);

	stat_inc_call_count(sbi->stat_info);

	return seg_freed;
}