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
struct victim_sel_policy {char alloc_mode; unsigned int min_segno; unsigned long min_cost; unsigned int max_search; size_t gc_mode; unsigned int offset; unsigned int ofs_unit; int /*<<< orphan*/  dirty_segmap; } ;
struct sit_info {unsigned int* last_victim; } ;
struct f2fs_sb_info {unsigned int cur_victim_sec; int /*<<< orphan*/  sb; } ;
struct dirty_seglist_info {int /*<<< orphan*/  seglist_lock; int /*<<< orphan*/  victim_secmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int BG_GC ; 
 struct dirty_seglist_info* DIRTY_I (struct f2fs_sb_info*) ; 
 int FG_GC ; 
 unsigned int GET_SEC_FROM_SEG (struct f2fs_sb_info*,unsigned int) ; 
 scalar_t__ IS_DATASEG (int /*<<< orphan*/ ) ; 
 char LFS ; 
 unsigned int MAIN_SEGS (struct f2fs_sb_info*) ; 
 unsigned int NULL_SEGNO ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 unsigned int check_bg_victims (struct f2fs_sb_info*) ; 
 scalar_t__ count_bits (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int find_next_bit (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  free_segments (struct f2fs_sb_info*) ; 
 unsigned long get_gc_cost (struct f2fs_sb_info*,unsigned int,struct victim_sel_policy*) ; 
 unsigned long get_max_cost (struct f2fs_sb_info*,struct victim_sel_policy*) ; 
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 scalar_t__ get_valid_blocks (struct f2fs_sb_info*,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefree_segments (struct f2fs_sb_info*) ; 
 scalar_t__ sec_usage_check (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  select_policy (struct f2fs_sb_info*,int,int,struct victim_sel_policy*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_get_victim (int /*<<< orphan*/ ,int,int,struct victim_sel_policy*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_victim_by_default(struct f2fs_sb_info *sbi,
		unsigned int *result, int gc_type, int type, char alloc_mode)
{
	struct dirty_seglist_info *dirty_i = DIRTY_I(sbi);
	struct sit_info *sm = SIT_I(sbi);
	struct victim_sel_policy p;
	unsigned int secno, last_victim;
	unsigned int last_segment = MAIN_SEGS(sbi);
	unsigned int nsearched = 0;

	mutex_lock(&dirty_i->seglist_lock);

	p.alloc_mode = alloc_mode;
	select_policy(sbi, gc_type, type, &p);

	p.min_segno = NULL_SEGNO;
	p.min_cost = get_max_cost(sbi, &p);

	if (*result != NULL_SEGNO) {
		if (IS_DATASEG(get_seg_entry(sbi, *result)->type) &&
			get_valid_blocks(sbi, *result, false) &&
			!sec_usage_check(sbi, GET_SEC_FROM_SEG(sbi, *result)))
			p.min_segno = *result;
		goto out;
	}

	if (p.max_search == 0)
		goto out;

	last_victim = sm->last_victim[p.gc_mode];
	if (p.alloc_mode == LFS && gc_type == FG_GC) {
		p.min_segno = check_bg_victims(sbi);
		if (p.min_segno != NULL_SEGNO)
			goto got_it;
	}

	while (1) {
		unsigned long cost;
		unsigned int segno;

		segno = find_next_bit(p.dirty_segmap, last_segment, p.offset);
		if (segno >= last_segment) {
			if (sm->last_victim[p.gc_mode]) {
				last_segment =
					sm->last_victim[p.gc_mode];
				sm->last_victim[p.gc_mode] = 0;
				p.offset = 0;
				continue;
			}
			break;
		}

		p.offset = segno + p.ofs_unit;
		if (p.ofs_unit > 1) {
			p.offset -= segno % p.ofs_unit;
			nsearched += count_bits(p.dirty_segmap,
						p.offset - p.ofs_unit,
						p.ofs_unit);
		} else {
			nsearched++;
		}

		secno = GET_SEC_FROM_SEG(sbi, segno);

		if (sec_usage_check(sbi, secno))
			goto next;
		if (gc_type == BG_GC && test_bit(secno, dirty_i->victim_secmap))
			goto next;

		cost = get_gc_cost(sbi, segno, &p);

		if (p.min_cost > cost) {
			p.min_segno = segno;
			p.min_cost = cost;
		}
next:
		if (nsearched >= p.max_search) {
			if (!sm->last_victim[p.gc_mode] && segno <= last_victim)
				sm->last_victim[p.gc_mode] = last_victim + 1;
			else
				sm->last_victim[p.gc_mode] = segno + 1;
			sm->last_victim[p.gc_mode] %= MAIN_SEGS(sbi);
			break;
		}
	}
	if (p.min_segno != NULL_SEGNO) {
got_it:
		if (p.alloc_mode == LFS) {
			secno = GET_SEC_FROM_SEG(sbi, p.min_segno);
			if (gc_type == FG_GC)
				sbi->cur_victim_sec = secno;
			else
				set_bit(secno, dirty_i->victim_secmap);
		}
		*result = (p.min_segno / p.ofs_unit) * p.ofs_unit;

		trace_f2fs_get_victim(sbi->sb, type, gc_type, &p,
				sbi->cur_victim_sec,
				prefree_segments(sbi), free_segments(sbi));
	}
out:
	mutex_unlock(&dirty_i->seglist_lock);

	return (p.min_segno == NULL_SEGNO) ? 0 : 1;
}