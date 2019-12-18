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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_journal {int dummy; } ;
struct TYPE_2__ {struct f2fs_journal* journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_COMPACT_SUM_FLAG ; 
 int CURSEG_COLD_DATA ; 
 int CURSEG_COLD_NODE ; 
 int CURSEG_HOT_DATA ; 
 int CURSEG_HOT_NODE ; 
 TYPE_1__* CURSEG_I (struct f2fs_sb_info*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  META_CP ; 
 scalar_t__ NAT_JOURNAL_ENTRIES ; 
 int NR_CURSEG_TYPE ; 
 scalar_t__ SIT_JOURNAL_ENTRIES ; 
 scalar_t__ __exist_node_summaries (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_err (struct f2fs_sb_info*,char*,scalar_t__,scalar_t__) ; 
 int f2fs_npages_for_summary_flush (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_ra_meta_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_set_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ nats_in_cursum (struct f2fs_journal*) ; 
 int read_compacted_summaries (struct f2fs_sb_info*) ; 
 int read_normal_summaries (struct f2fs_sb_info*,int) ; 
 scalar_t__ sits_in_cursum (struct f2fs_journal*) ; 
 int /*<<< orphan*/  start_sum_block (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  sum_blk_addr (struct f2fs_sb_info*,int,int) ; 

__attribute__((used)) static int restore_curseg_summaries(struct f2fs_sb_info *sbi)
{
	struct f2fs_journal *sit_j = CURSEG_I(sbi, CURSEG_COLD_DATA)->journal;
	struct f2fs_journal *nat_j = CURSEG_I(sbi, CURSEG_HOT_DATA)->journal;
	int type = CURSEG_HOT_DATA;
	int err;

	if (is_set_ckpt_flags(sbi, CP_COMPACT_SUM_FLAG)) {
		int npages = f2fs_npages_for_summary_flush(sbi, true);

		if (npages >= 2)
			f2fs_ra_meta_pages(sbi, start_sum_block(sbi), npages,
							META_CP, true);

		/* restore for compacted data summary */
		err = read_compacted_summaries(sbi);
		if (err)
			return err;
		type = CURSEG_HOT_NODE;
	}

	if (__exist_node_summaries(sbi))
		f2fs_ra_meta_pages(sbi, sum_blk_addr(sbi, NR_CURSEG_TYPE, type),
					NR_CURSEG_TYPE - type, META_CP, true);

	for (; type <= CURSEG_COLD_NODE; type++) {
		err = read_normal_summaries(sbi, type);
		if (err)
			return err;
	}

	/* sanity check for summary blocks */
	if (nats_in_cursum(nat_j) > NAT_JOURNAL_ENTRIES ||
			sits_in_cursum(sit_j) > SIT_JOURNAL_ENTRIES) {
		f2fs_err(sbi, "invalid journal entries nats %u sits %u\n",
			 nats_in_cursum(nat_j), sits_in_cursum(sit_j));
		return -EINVAL;
	}

	return 0;
}