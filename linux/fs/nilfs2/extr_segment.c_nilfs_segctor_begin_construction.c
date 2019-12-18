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
struct the_nilfs {int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_nextnum; int /*<<< orphan*/  ns_segnum; int /*<<< orphan*/  ns_seg_seq; int /*<<< orphan*/  ns_pseg_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  seg_seq; } ;
struct nilfs_segment_buffer {scalar_t__ sb_rest_blocks; int /*<<< orphan*/  sb_list; int /*<<< orphan*/  sb_segnum; TYPE_1__ sb_sum; int /*<<< orphan*/  sb_nextnum; } ;
struct nilfs_sc_info {scalar_t__ sc_segbuf_nblocks; int /*<<< orphan*/  sc_segbufs; int /*<<< orphan*/  sc_write_logs; int /*<<< orphan*/  sc_super; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct nilfs_segment_buffer* NILFS_LAST_SEGBUF (int /*<<< orphan*/ *) ; 
 scalar_t__ NILFS_PSEG_MIN_BLOCKS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_segbuf_free (struct nilfs_segment_buffer*) ; 
 int /*<<< orphan*/  nilfs_segbuf_map (struct nilfs_segment_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_segbuf_map_cont (struct nilfs_segment_buffer*,struct nilfs_segment_buffer*) ; 
 struct nilfs_segment_buffer* nilfs_segbuf_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_segbuf_set_next_segnum (struct nilfs_segment_buffer*,int /*<<< orphan*/ ,struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_shift_to_next_segment (struct the_nilfs*) ; 
 int nilfs_sufile_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nilfs_sufile_mark_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_segctor_begin_construction(struct nilfs_sc_info *sci,
					    struct the_nilfs *nilfs)
{
	struct nilfs_segment_buffer *segbuf, *prev;
	__u64 nextnum;
	int err, alloc = 0;

	segbuf = nilfs_segbuf_new(sci->sc_super);
	if (unlikely(!segbuf))
		return -ENOMEM;

	if (list_empty(&sci->sc_write_logs)) {
		nilfs_segbuf_map(segbuf, nilfs->ns_segnum,
				 nilfs->ns_pseg_offset, nilfs);
		if (segbuf->sb_rest_blocks < NILFS_PSEG_MIN_BLOCKS) {
			nilfs_shift_to_next_segment(nilfs);
			nilfs_segbuf_map(segbuf, nilfs->ns_segnum, 0, nilfs);
		}

		segbuf->sb_sum.seg_seq = nilfs->ns_seg_seq;
		nextnum = nilfs->ns_nextnum;

		if (nilfs->ns_segnum == nilfs->ns_nextnum)
			/* Start from the head of a new full segment */
			alloc++;
	} else {
		/* Continue logs */
		prev = NILFS_LAST_SEGBUF(&sci->sc_write_logs);
		nilfs_segbuf_map_cont(segbuf, prev);
		segbuf->sb_sum.seg_seq = prev->sb_sum.seg_seq;
		nextnum = prev->sb_nextnum;

		if (segbuf->sb_rest_blocks < NILFS_PSEG_MIN_BLOCKS) {
			nilfs_segbuf_map(segbuf, prev->sb_nextnum, 0, nilfs);
			segbuf->sb_sum.seg_seq++;
			alloc++;
		}
	}

	err = nilfs_sufile_mark_dirty(nilfs->ns_sufile, segbuf->sb_segnum);
	if (err)
		goto failed;

	if (alloc) {
		err = nilfs_sufile_alloc(nilfs->ns_sufile, &nextnum);
		if (err)
			goto failed;
	}
	nilfs_segbuf_set_next_segnum(segbuf, nextnum, nilfs);

	BUG_ON(!list_empty(&sci->sc_segbufs));
	list_add_tail(&segbuf->sb_list, &sci->sc_segbufs);
	sci->sc_segbuf_nblocks = segbuf->sb_rest_blocks;
	return 0;

 failed:
	nilfs_segbuf_free(segbuf);
	return err;
}