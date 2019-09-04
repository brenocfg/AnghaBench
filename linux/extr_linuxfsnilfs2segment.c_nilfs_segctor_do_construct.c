#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct the_nilfs {scalar_t__ ns_blocksize_bits; int /*<<< orphan*/  ns_crc_seed; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_cno; } ;
struct TYPE_4__ {int flags; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_gc_inodes; int /*<<< orphan*/  sc_dirty_files; TYPE_2__ sc_stage; int /*<<< orphan*/  sc_segbufs; int /*<<< orphan*/  sc_curseg; int /*<<< orphan*/  sc_seg_ctime; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_root; int /*<<< orphan*/  sc_cno; TYPE_1__* sc_super; } ;
struct TYPE_3__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int NILFS_CF_HISTORY_MASK ; 
 int NILFS_CF_IFILE_STARTED ; 
 int /*<<< orphan*/  NILFS_SC_DIRTY ; 
 scalar_t__ NILFS_ST_CPFILE ; 
 scalar_t__ NILFS_ST_DONE ; 
 int /*<<< orphan*/  NILFS_ST_INIT ; 
 scalar_t__ PAGE_SHIFT ; 
 int SC_LSEG_SR ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  nilfs_add_checksums_on_logs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_doing_gc () ; 
 int /*<<< orphan*/  nilfs_redirty_inodes (int /*<<< orphan*/ *) ; 
 scalar_t__ nilfs_sc_cstage_get (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_sc_cstage_set (struct nilfs_sc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_segbuf_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_segctor_abort_construction (struct nilfs_sc_info*,struct the_nilfs*,int) ; 
 int nilfs_segctor_assign (struct nilfs_sc_info*,int) ; 
 int nilfs_segctor_begin_construction (struct nilfs_sc_info*,struct the_nilfs*) ; 
 scalar_t__ nilfs_segctor_clean (struct nilfs_sc_info*) ; 
 int nilfs_segctor_collect (struct nilfs_sc_info*,struct the_nilfs*,int) ; 
 int nilfs_segctor_collect_dirty_files (struct nilfs_sc_info*,struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_segctor_drop_written_files (struct nilfs_sc_info*,struct the_nilfs*) ; 
 int nilfs_segctor_fill_in_checkpoint (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_fill_in_file_bmap (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_fill_in_super_root (struct nilfs_sc_info*,struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_segctor_prepare_write (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_update_segusage (struct nilfs_sc_info*,int /*<<< orphan*/ ) ; 
 int nilfs_segctor_wait (struct nilfs_sc_info*) ; 
 int nilfs_segctor_write (struct nilfs_sc_info*,struct the_nilfs*) ; 
 scalar_t__ nilfs_test_metadata_dirty (struct the_nilfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_segctor_do_construct(struct nilfs_sc_info *sci, int mode)
{
	struct the_nilfs *nilfs = sci->sc_super->s_fs_info;
	int err;

	nilfs_sc_cstage_set(sci, NILFS_ST_INIT);
	sci->sc_cno = nilfs->ns_cno;

	err = nilfs_segctor_collect_dirty_files(sci, nilfs);
	if (unlikely(err))
		goto out;

	if (nilfs_test_metadata_dirty(nilfs, sci->sc_root))
		set_bit(NILFS_SC_DIRTY, &sci->sc_flags);

	if (nilfs_segctor_clean(sci))
		goto out;

	do {
		sci->sc_stage.flags &= ~NILFS_CF_HISTORY_MASK;

		err = nilfs_segctor_begin_construction(sci, nilfs);
		if (unlikely(err))
			goto out;

		/* Update time stamp */
		sci->sc_seg_ctime = ktime_get_real_seconds();

		err = nilfs_segctor_collect(sci, nilfs, mode);
		if (unlikely(err))
			goto failed;

		/* Avoid empty segment */
		if (nilfs_sc_cstage_get(sci) == NILFS_ST_DONE &&
		    nilfs_segbuf_empty(sci->sc_curseg)) {
			nilfs_segctor_abort_construction(sci, nilfs, 1);
			goto out;
		}

		err = nilfs_segctor_assign(sci, mode);
		if (unlikely(err))
			goto failed;

		if (sci->sc_stage.flags & NILFS_CF_IFILE_STARTED)
			nilfs_segctor_fill_in_file_bmap(sci);

		if (mode == SC_LSEG_SR &&
		    nilfs_sc_cstage_get(sci) >= NILFS_ST_CPFILE) {
			err = nilfs_segctor_fill_in_checkpoint(sci);
			if (unlikely(err))
				goto failed_to_write;

			nilfs_segctor_fill_in_super_root(sci, nilfs);
		}
		nilfs_segctor_update_segusage(sci, nilfs->ns_sufile);

		/* Write partial segments */
		nilfs_segctor_prepare_write(sci);

		nilfs_add_checksums_on_logs(&sci->sc_segbufs,
					    nilfs->ns_crc_seed);

		err = nilfs_segctor_write(sci, nilfs);
		if (unlikely(err))
			goto failed_to_write;

		if (nilfs_sc_cstage_get(sci) == NILFS_ST_DONE ||
		    nilfs->ns_blocksize_bits != PAGE_SHIFT) {
			/*
			 * At this point, we avoid double buffering
			 * for blocksize < pagesize because page dirty
			 * flag is turned off during write and dirty
			 * buffers are not properly collected for
			 * pages crossing over segments.
			 */
			err = nilfs_segctor_wait(sci);
			if (err)
				goto failed_to_write;
		}
	} while (nilfs_sc_cstage_get(sci) != NILFS_ST_DONE);

 out:
	nilfs_segctor_drop_written_files(sci, nilfs);
	return err;

 failed_to_write:
	if (sci->sc_stage.flags & NILFS_CF_IFILE_STARTED)
		nilfs_redirty_inodes(&sci->sc_dirty_files);

 failed:
	if (nilfs_doing_gc())
		nilfs_redirty_inodes(&sci->sc_gc_inodes);
	nilfs_segctor_abort_construction(sci, nilfs, err);
	goto out;
}