#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct the_nilfs {int /*<<< orphan*/  ns_sem; int /*<<< orphan*/  ns_ndirtyblks; } ;
struct nilfs_super_block {int dummy; } ;
struct nilfs_sc_info {TYPE_1__* sc_super; int /*<<< orphan*/  sc_flags; } ;
struct TYPE_3__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NILFS_SB_COMMIT ; 
 int /*<<< orphan*/  NILFS_SC_SUPER_ROOT ; 
 int SC_FLUSH_DAT ; 
 int SC_LSEG_SR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int nilfs_commit_super (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_discontinued (struct the_nilfs*) ; 
 struct nilfs_super_block** nilfs_prepare_super (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_sb_will_flip (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_segctor_accept (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_confirm (struct nilfs_sc_info*) ; 
 int nilfs_segctor_do_construct (struct nilfs_sc_info*,int) ; 
 int /*<<< orphan*/  nilfs_segctor_notify (struct nilfs_sc_info*,int,int) ; 
 int /*<<< orphan*/  nilfs_set_log_cursor (struct nilfs_super_block*,struct the_nilfs*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segctor_construct(struct nilfs_sc_info *sci, int mode)
{
	struct the_nilfs *nilfs = sci->sc_super->s_fs_info;
	struct nilfs_super_block **sbp;
	int err = 0;

	nilfs_segctor_accept(sci);

	if (nilfs_discontinued(nilfs))
		mode = SC_LSEG_SR;
	if (!nilfs_segctor_confirm(sci))
		err = nilfs_segctor_do_construct(sci, mode);

	if (likely(!err)) {
		if (mode != SC_FLUSH_DAT)
			atomic_set(&nilfs->ns_ndirtyblks, 0);
		if (test_bit(NILFS_SC_SUPER_ROOT, &sci->sc_flags) &&
		    nilfs_discontinued(nilfs)) {
			down_write(&nilfs->ns_sem);
			err = -EIO;
			sbp = nilfs_prepare_super(sci->sc_super,
						  nilfs_sb_will_flip(nilfs));
			if (likely(sbp)) {
				nilfs_set_log_cursor(sbp[0], nilfs);
				err = nilfs_commit_super(sci->sc_super,
							 NILFS_SB_COMMIT);
			}
			up_write(&nilfs->ns_sem);
		}
	}

	nilfs_segctor_notify(sci, mode, err);
	return err;
}