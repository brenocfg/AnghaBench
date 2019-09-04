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
struct fc_vport {scalar_t__ dd_data; } ;
struct csio_lnode {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_DISABLED ; 
 int /*<<< orphan*/  FC_VPORT_INITIALIZING ; 
 scalar_t__ csio_fcoe_alloc_vnp (struct csio_hw*,struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_fcoe_free_vnp (struct csio_hw*,struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*) ; 
 struct Scsi_Host* csio_ln_to_shost (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lnode_stop (struct csio_lnode*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_scsim_cleanup_io_lnode (int /*<<< orphan*/ ,struct csio_lnode*) ; 
 int /*<<< orphan*/  fc_vport_set_state (struct fc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_unblock_requests (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
csio_vport_disable(struct fc_vport *fc_vport, bool disable)
{
	struct csio_lnode *ln = *(struct csio_lnode **)fc_vport->dd_data;
	struct Scsi_Host *shost = csio_ln_to_shost(ln);
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	/* disable vport */
	if (disable) {
		/* Quiesce ios and send stop event to lnode */
		scsi_block_requests(shost);
		spin_lock_irq(&hw->lock);
		csio_scsim_cleanup_io_lnode(csio_hw_to_scsim(hw), ln);
		csio_lnode_stop(ln);
		spin_unlock_irq(&hw->lock);
		scsi_unblock_requests(shost);

		/* Free vnp */
		csio_fcoe_free_vnp(hw, ln);
		fc_vport_set_state(fc_vport, FC_VPORT_DISABLED);
		csio_ln_err(ln, "vport disabled\n");
		return 0;
	} else {
		/* enable vport */
		fc_vport_set_state(fc_vport, FC_VPORT_INITIALIZING);
		if (csio_fcoe_alloc_vnp(hw, ln)) {
			csio_ln_err(ln, "vport enabled failed.\n");
			return -1;
		}
		csio_ln_err(ln, "vport enabled\n");
		return 0;
	}
}