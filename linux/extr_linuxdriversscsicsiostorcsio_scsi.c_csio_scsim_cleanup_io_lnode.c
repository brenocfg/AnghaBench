#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct csio_scsim {struct csio_hw* hw; } ;
struct csio_scsi_level_data {struct csio_lnode* lnode; int /*<<< orphan*/  level; } ;
struct csio_lnode {int /*<<< orphan*/  cmpl_q; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  CSIO_LEV_LNODE ; 
 int /*<<< orphan*/  CSIO_SCSI_ABORT_Q_POLL_MS ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,...) ; 
 int csio_scsi_abort_io_q (struct csio_scsim*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  csio_scsi_cleanup_io_q (struct csio_scsim*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_scsi_gather_active_ios (struct csio_scsim*,struct csio_scsi_level_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
csio_scsim_cleanup_io_lnode(struct csio_scsim *scm, struct csio_lnode *ln)
{
	struct csio_hw *hw = scm->hw;
	struct csio_scsi_level_data sld;
	int rv;
	int count = DIV_ROUND_UP(60 * 1000, CSIO_SCSI_ABORT_Q_POLL_MS);

	csio_dbg(hw, "Gathering all SCSI I/Os on lnode %p\n", ln);

	sld.level = CSIO_LEV_LNODE;
	sld.lnode = ln;
	INIT_LIST_HEAD(&ln->cmpl_q);
	csio_scsi_gather_active_ios(scm, &sld, &ln->cmpl_q);

	/* No I/Os pending on this lnode  */
	if (list_empty(&ln->cmpl_q))
		return 0;

	/* Wait until all active I/Os on this lnode are completed */
	while (!list_empty(&ln->cmpl_q) && count--) {
		spin_unlock_irq(&hw->lock);
		msleep(CSIO_SCSI_ABORT_Q_POLL_MS);
		spin_lock_irq(&hw->lock);
	}

	/* all I/Os completed */
	if (list_empty(&ln->cmpl_q))
		return 0;

	csio_dbg(hw, "Some I/Os pending on ln:%p, aborting them..\n", ln);

	/* I/Os are pending, abort them */
	rv = csio_scsi_abort_io_q(scm, &ln->cmpl_q, 30000);
	if (rv != 0) {
		csio_dbg(hw, "Some I/O aborts timed out, cleaning up..\n");
		csio_scsi_cleanup_io_q(scm, &ln->cmpl_q);
	}

	CSIO_DB_ASSERT(list_empty(&ln->cmpl_q));

	return rv;
}