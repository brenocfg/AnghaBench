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
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; struct nilfs_sc_info* ns_writer; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_transaction_info {int /*<<< orphan*/  ti_flags; scalar_t__ ti_count; int /*<<< orphan*/  ti_magic; struct nilfs_transaction_info* ti_save; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_flags; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SC_PRIOR_FLUSH ; 
 int /*<<< orphan*/  NILFS_TI_GC ; 
 int /*<<< orphan*/  NILFS_TI_MAGIC ; 
 int /*<<< orphan*/  NILFS_TI_WRITER ; 
 int /*<<< orphan*/  TRACE_NILFS2_TRANSACTION_LOCK ; 
 int /*<<< orphan*/  TRACE_NILFS2_TRANSACTION_TRYLOCK ; 
 int /*<<< orphan*/  WARN_ON (struct nilfs_transaction_info*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_segctor_do_immediate_flush (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nilfs2_transaction_transition (struct super_block*,struct nilfs_transaction_info*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_transaction_lock(struct super_block *sb,
				   struct nilfs_transaction_info *ti,
				   int gcflag)
{
	struct nilfs_transaction_info *cur_ti = current->journal_info;
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_sc_info *sci = nilfs->ns_writer;

	WARN_ON(cur_ti);
	ti->ti_flags = NILFS_TI_WRITER;
	ti->ti_count = 0;
	ti->ti_save = cur_ti;
	ti->ti_magic = NILFS_TI_MAGIC;
	current->journal_info = ti;

	for (;;) {
		trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_TRYLOCK);

		down_write(&nilfs->ns_segctor_sem);
		if (!test_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags))
			break;

		nilfs_segctor_do_immediate_flush(sci);

		up_write(&nilfs->ns_segctor_sem);
		cond_resched();
	}
	if (gcflag)
		ti->ti_flags |= NILFS_TI_GC;

	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_LOCK);
}