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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int size; scalar_t__ index; int /*<<< orphan*/  base_addr; } ;
struct scsi_info {int flags; scalar_t__ new_state; scalar_t__ phyp_acr_state; int phyp_acr_flags; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; TYPE_1__ cmd_q; int /*<<< orphan*/  intr_lock; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
 int CRQ_CLOSED ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ibmvscsis_delete_client_info (struct scsi_info*,int) ; 
 long ibmvscsis_unregister_command_q (struct scsi_info*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_disable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ibmvscsis_free_command_q(struct scsi_info *vscsi)
{
	int bytes;
	u32 flags_under_lock;
	u16 state_under_lock;
	long rc = ADAPT_SUCCESS;

	if (!(vscsi->flags & CRQ_CLOSED)) {
		vio_disable_interrupts(vscsi->dma_dev);

		state_under_lock = vscsi->new_state;
		flags_under_lock = vscsi->flags;
		vscsi->phyp_acr_state = 0;
		vscsi->phyp_acr_flags = 0;

		spin_unlock_bh(&vscsi->intr_lock);
		rc = ibmvscsis_unregister_command_q(vscsi);
		spin_lock_bh(&vscsi->intr_lock);

		if (state_under_lock != vscsi->new_state)
			vscsi->phyp_acr_state = vscsi->new_state;

		vscsi->phyp_acr_flags = ((~flags_under_lock) & vscsi->flags);

		if (rc == ADAPT_SUCCESS) {
			bytes = vscsi->cmd_q.size * PAGE_SIZE;
			memset(vscsi->cmd_q.base_addr, 0, bytes);
			vscsi->cmd_q.index = 0;
			vscsi->flags |= CRQ_CLOSED;

			ibmvscsis_delete_client_info(vscsi, false);
		}

		dev_dbg(&vscsi->dev, "free_command_q: flags 0x%x, state 0x%hx, acr_flags 0x%x, acr_state 0x%hx\n",
			vscsi->flags, vscsi->state, vscsi->phyp_acr_flags,
			vscsi->phyp_acr_state);
	}
	return rc;
}