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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct fw_wr_hdr {int /*<<< orphan*/  hi; } ;
struct TYPE_2__ {int /*<<< orphan*/  fcoe_rdev; } ;
struct fw_rdev_wr {size_t event_cause; scalar_t__ protocol; TYPE_1__ u; int /*<<< orphan*/  flags_to_assoc_flowid; int /*<<< orphan*/  alloc_to_len16; } ;
struct fw_fcoe_link_cmd {int lstatus; int /*<<< orphan*/  vnpi_pkd; int /*<<< orphan*/  sub_opcode_fcfi; int /*<<< orphan*/  op_to_portid; } ;
struct fw_fcoe_els_ct_wr {int dummy; } ;
struct csio_rnode {int dummy; } ;
struct csio_lnode {size_t prev_evt; size_t cur_evt; int /*<<< orphan*/  lock; int /*<<< orphan*/  sm; } ;
struct csio_hw {size_t prev_evt; size_t cur_evt; int /*<<< orphan*/  lock; int /*<<< orphan*/  sm; } ;
typedef  enum fw_fcoe_link_status { ____Placeholder_fw_fcoe_link_status } fw_fcoe_link_status ;
typedef  enum csio_ln_ev { ____Placeholder_csio_ln_ev } csio_ln_ev ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ CPL_FW6_MSG ; 
 scalar_t__ CPL_FW6_PLD ; 
 int CSIO_FWE_TO_LNE (size_t) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int FCOE_LINKDOWN ; 
 int FCOE_LINKUP ; 
 scalar_t__ FW_FCOE_ELS_CT_WR ; 
 scalar_t__ FW_FCOE_LINK_CMD ; 
 scalar_t__ FW_FCOE_LINK_CMD_FCFI_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_FCOE_LINK_CMD_PORTID_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_FCOE_LINK_CMD_VNPI_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_RDEV_WR ; 
 scalar_t__ FW_RDEV_WR_ASSOC_FLOWID_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_RDEV_WR_FLOWID_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_WR_OP_G (int /*<<< orphan*/ ) ; 
 scalar_t__ PROT_FCOE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct csio_rnode* csio_confirm_rnode (struct csio_lnode*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_dbg (struct csio_lnode*,char*,scalar_t__,size_t,scalar_t__) ; 
 int /*<<< orphan*/  csio_err (struct csio_lnode*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  csio_handle_link_down (struct csio_lnode*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  csio_handle_link_up (struct csio_lnode*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,int,...) ; 
 struct csio_lnode* csio_ln_lookup_by_vnpi (struct csio_lnode*,scalar_t__) ; 
 int /*<<< orphan*/  csio_ln_mgmt_wr_handler (struct csio_lnode*,struct fw_wr_hdr*,int) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  csio_rnode_fwevt_handler (struct csio_rnode*,size_t) ; 
 int /*<<< orphan*/  csio_warn (struct csio_lnode*,char*,scalar_t__) ; 
 int /*<<< orphan*/  n_cpl_unexp ; 
 int /*<<< orphan*/  n_evt_drop ; 
 int /*<<< orphan*/ * n_evt_fw ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
csio_fcoe_fwevt_handler(struct csio_hw *hw, __u8 cpl_op, __be64 *cmd)
{
	struct csio_lnode *ln;
	struct csio_rnode *rn;
	uint8_t portid, opcode = *(uint8_t *)cmd;
	struct fw_fcoe_link_cmd *lcmd;
	struct fw_wr_hdr *wr;
	struct fw_rdev_wr *rdev_wr;
	enum fw_fcoe_link_status lstatus;
	uint32_t fcfi, rdev_flowid, vnpi;
	enum csio_ln_ev evt;

	if (cpl_op == CPL_FW6_MSG && opcode == FW_FCOE_LINK_CMD) {

		lcmd = (struct fw_fcoe_link_cmd *)cmd;
		lstatus = lcmd->lstatus;
		portid = FW_FCOE_LINK_CMD_PORTID_GET(
					ntohl(lcmd->op_to_portid));
		fcfi = FW_FCOE_LINK_CMD_FCFI_GET(ntohl(lcmd->sub_opcode_fcfi));
		vnpi = FW_FCOE_LINK_CMD_VNPI_GET(ntohl(lcmd->vnpi_pkd));

		if (lstatus == FCOE_LINKUP) {

			/* HW lock here */
			spin_lock_irq(&hw->lock);
			csio_handle_link_up(hw, portid, fcfi, vnpi);
			spin_unlock_irq(&hw->lock);
			/* HW un lock here */

		} else if (lstatus == FCOE_LINKDOWN) {

			/* HW lock here */
			spin_lock_irq(&hw->lock);
			csio_handle_link_down(hw, portid, fcfi, vnpi);
			spin_unlock_irq(&hw->lock);
			/* HW un lock here */
		} else {
			csio_warn(hw, "Unexpected FCOE LINK status:0x%x\n",
				  lcmd->lstatus);
			CSIO_INC_STATS(hw, n_cpl_unexp);
		}
	} else if (cpl_op == CPL_FW6_PLD) {
		wr = (struct fw_wr_hdr *) (cmd + 4);
		if (FW_WR_OP_G(be32_to_cpu(wr->hi))
			== FW_RDEV_WR) {

			rdev_wr = (struct fw_rdev_wr *) (cmd + 4);

			rdev_flowid = FW_RDEV_WR_FLOWID_GET(
					ntohl(rdev_wr->alloc_to_len16));
			vnpi = FW_RDEV_WR_ASSOC_FLOWID_GET(
				    ntohl(rdev_wr->flags_to_assoc_flowid));

			csio_dbg(hw,
				"FW_RDEV_WR: flowid:x%x ev_cause:x%x "
				"vnpi:0x%x\n", rdev_flowid,
				rdev_wr->event_cause, vnpi);

			if (rdev_wr->protocol != PROT_FCOE) {
				csio_err(hw,
					"FW_RDEV_WR: invalid proto:x%x "
					"received with flowid:x%x\n",
					rdev_wr->protocol,
					rdev_flowid);
				CSIO_INC_STATS(hw, n_evt_drop);
				return;
			}

			/* HW lock here */
			spin_lock_irq(&hw->lock);
			ln = csio_ln_lookup_by_vnpi(hw, vnpi);
			if (!ln) {
				csio_err(hw,
					"FW_DEV_WR: invalid vnpi:x%x received "
					"with flowid:x%x\n", vnpi, rdev_flowid);
				CSIO_INC_STATS(hw, n_evt_drop);
				goto out_pld;
			}

			rn = csio_confirm_rnode(ln, rdev_flowid,
					&rdev_wr->u.fcoe_rdev);
			if (!rn) {
				csio_ln_dbg(ln,
					"Failed to confirm rnode "
					"for flowid:x%x\n", rdev_flowid);
				CSIO_INC_STATS(hw, n_evt_drop);
				goto out_pld;
			}

			/* save previous event for debugging */
			ln->prev_evt = ln->cur_evt;
			ln->cur_evt = rdev_wr->event_cause;
			CSIO_INC_STATS(ln, n_evt_fw[rdev_wr->event_cause]);

			/* Translate all the fabric events to lnode SM events */
			evt = CSIO_FWE_TO_LNE(rdev_wr->event_cause);
			if (evt) {
				csio_ln_dbg(ln,
					"Posting event to lnode event:%d "
					"cause:%d flowid:x%x\n", evt,
					rdev_wr->event_cause, rdev_flowid);
				csio_post_event(&ln->sm, evt);
			}

			/* Handover event to rn SM here. */
			csio_rnode_fwevt_handler(rn, rdev_wr->event_cause);
out_pld:
			spin_unlock_irq(&hw->lock);
			return;
		} else {
			csio_warn(hw, "unexpected WR op(0x%x) recv\n",
				  FW_WR_OP_G(be32_to_cpu((wr->hi))));
			CSIO_INC_STATS(hw, n_cpl_unexp);
		}
	} else if (cpl_op == CPL_FW6_MSG) {
		wr = (struct fw_wr_hdr *) (cmd);
		if (FW_WR_OP_G(be32_to_cpu(wr->hi)) == FW_FCOE_ELS_CT_WR) {
			csio_ln_mgmt_wr_handler(hw, wr,
					sizeof(struct fw_fcoe_els_ct_wr));
		} else {
			csio_warn(hw, "unexpected WR op(0x%x) recv\n",
				  FW_WR_OP_G(be32_to_cpu((wr->hi))));
			CSIO_INC_STATS(hw, n_cpl_unexp);
		}
	} else {
		csio_warn(hw, "unexpected CPL op(0x%x) recv\n", opcode);
		CSIO_INC_STATS(hw, n_cpl_unexp);
	}
}