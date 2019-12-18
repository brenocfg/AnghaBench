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
struct nilfs_transaction_info {int /*<<< orphan*/  ti_flags; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_flags; scalar_t__ sc_flush_request; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SC_PRIOR_FLUSH ; 
 int /*<<< orphan*/  NILFS_TI_WRITER ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_segctor_do_immediate_flush (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void nilfs_relax_pressure_in_lock(struct super_block *sb)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_sc_info *sci = nilfs->ns_writer;

	if (!sci || !sci->sc_flush_request)
		return;

	set_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags);
	up_read(&nilfs->ns_segctor_sem);

	down_write(&nilfs->ns_segctor_sem);
	if (sci->sc_flush_request &&
	    test_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags)) {
		struct nilfs_transaction_info *ti = current->journal_info;

		ti->ti_flags |= NILFS_TI_WRITER;
		nilfs_segctor_do_immediate_flush(sci);
		ti->ti_flags &= ~NILFS_TI_WRITER;
	}
	downgrade_write(&nilfs->ns_segctor_sem);
}