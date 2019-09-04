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
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_ndirtyblks; struct nilfs_sc_info* ns_writer; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_transaction_info {scalar_t__ ti_magic; int ti_flags; scalar_t__ ti_count; struct nilfs_transaction_info* ti_save; } ;
struct nilfs_sc_info {scalar_t__ sc_watermark; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NILFS_TI_COMMIT ; 
 int NILFS_TI_DYNAMIC_ALLOC ; 
 scalar_t__ NILFS_TI_MAGIC ; 
 int NILFS_TI_SYNC ; 
 int /*<<< orphan*/  TRACE_NILFS2_TRANSACTION_COMMIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nilfs_transaction_info*) ; 
 int nilfs_construct_segment (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_segctor_do_flush (struct nilfs_sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_segctor_start_timer (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_transaction_cachep ; 
 int /*<<< orphan*/  sb_end_intwrite (struct super_block*) ; 
 int /*<<< orphan*/  trace_nilfs2_transaction_transition (struct super_block*,struct nilfs_transaction_info*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_transaction_commit(struct super_block *sb)
{
	struct nilfs_transaction_info *ti = current->journal_info;
	struct the_nilfs *nilfs = sb->s_fs_info;
	int err = 0;

	BUG_ON(ti == NULL || ti->ti_magic != NILFS_TI_MAGIC);
	ti->ti_flags |= NILFS_TI_COMMIT;
	if (ti->ti_count > 0) {
		ti->ti_count--;
		trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_COMMIT);
		return 0;
	}
	if (nilfs->ns_writer) {
		struct nilfs_sc_info *sci = nilfs->ns_writer;

		if (ti->ti_flags & NILFS_TI_COMMIT)
			nilfs_segctor_start_timer(sci);
		if (atomic_read(&nilfs->ns_ndirtyblks) > sci->sc_watermark)
			nilfs_segctor_do_flush(sci, 0);
	}
	up_read(&nilfs->ns_segctor_sem);
	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_COMMIT);

	current->journal_info = ti->ti_save;

	if (ti->ti_flags & NILFS_TI_SYNC)
		err = nilfs_construct_segment(sb);
	if (ti->ti_flags & NILFS_TI_DYNAMIC_ALLOC)
		kmem_cache_free(nilfs_transaction_cachep, ti);
	sb_end_intwrite(sb);
	return err;
}