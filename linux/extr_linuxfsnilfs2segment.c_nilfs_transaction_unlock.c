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
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_transaction_info {scalar_t__ ti_magic; scalar_t__ ti_count; int /*<<< orphan*/  ti_flags; struct nilfs_transaction_info* ti_save; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NILFS_TI_MAGIC ; 
 int /*<<< orphan*/  TRACE_NILFS2_TRANSACTION_UNLOCK ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  trace_nilfs2_transaction_transition (struct super_block*,struct nilfs_transaction_info*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_transaction_unlock(struct super_block *sb)
{
	struct nilfs_transaction_info *ti = current->journal_info;
	struct the_nilfs *nilfs = sb->s_fs_info;

	BUG_ON(ti == NULL || ti->ti_magic != NILFS_TI_MAGIC);
	BUG_ON(ti->ti_count > 0);

	up_write(&nilfs->ns_segctor_sem);
	current->journal_info = ti->ti_save;

	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_UNLOCK);
}