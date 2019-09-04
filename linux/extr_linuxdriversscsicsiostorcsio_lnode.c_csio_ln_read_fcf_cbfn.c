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
struct fw_fcoe_fcf_cmd {int /*<<< orphan*/  spma_mac; int /*<<< orphan*/  fabric; int /*<<< orphan*/  name_id; int /*<<< orphan*/  mac; int /*<<< orphan*/  fc_map; int /*<<< orphan*/  fpma_to_portid; int /*<<< orphan*/  op_to_fcfi; int /*<<< orphan*/  fka_adv; int /*<<< orphan*/  max_fcoe_size; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  priority_pkd; int /*<<< orphan*/  retval_len16; } ;
struct csio_mb {scalar_t__ mb; scalar_t__ priv; } ;
struct csio_lnode {struct csio_fcf_info* fcfinfo; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; int /*<<< orphan*/  lock; } ;
struct csio_fcf_info {int /*<<< orphan*/  spma_mac; int /*<<< orphan*/  fabric; int /*<<< orphan*/  name_id; int /*<<< orphan*/  mac; int /*<<< orphan*/  fc_map; int /*<<< orphan*/  portid; int /*<<< orphan*/  login; int /*<<< orphan*/  spma; int /*<<< orphan*/  fpma; int /*<<< orphan*/  fcfi; int /*<<< orphan*/  fka_adv; void* max_fcoe_size; int /*<<< orphan*/  vlan_id; void* vf_id; int /*<<< orphan*/  priority; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;

/* Variables and functions */
 int FW_CMD_RETVAL_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_FCOE_FCF_CMD_FCFI_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_FCOE_FCF_CMD_FPMA_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_FCOE_FCF_CMD_LOGIN_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_FCOE_FCF_CMD_PORTID_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_FCOE_FCF_CMD_PRIORITY_GET (void*) ; 
 int /*<<< orphan*/  FW_FCOE_FCF_CMD_SPMA_GET (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_ln_read_fcf_cbfn(struct csio_hw *hw, struct csio_mb *mbp)
{
	struct csio_lnode *ln = (struct csio_lnode *)mbp->priv;
	struct csio_fcf_info	*fcf_info;
	struct fw_fcoe_fcf_cmd *rsp =
				(struct fw_fcoe_fcf_cmd *)(mbp->mb);
	enum fw_retval retval;

	retval = FW_CMD_RETVAL_G(ntohl(rsp->retval_len16));
	if (retval != FW_SUCCESS) {
		csio_ln_err(ln, "FCOE FCF cmd failed with ret x%x\n",
				retval);
		mempool_free(mbp, hw->mb_mempool);
		return;
	}

	spin_lock_irq(&hw->lock);
	fcf_info = ln->fcfinfo;
	fcf_info->priority = FW_FCOE_FCF_CMD_PRIORITY_GET(
					ntohs(rsp->priority_pkd));
	fcf_info->vf_id = ntohs(rsp->vf_id);
	fcf_info->vlan_id = rsp->vlan_id;
	fcf_info->max_fcoe_size = ntohs(rsp->max_fcoe_size);
	fcf_info->fka_adv = be32_to_cpu(rsp->fka_adv);
	fcf_info->fcfi = FW_FCOE_FCF_CMD_FCFI_GET(ntohl(rsp->op_to_fcfi));
	fcf_info->fpma = FW_FCOE_FCF_CMD_FPMA_GET(rsp->fpma_to_portid);
	fcf_info->spma = FW_FCOE_FCF_CMD_SPMA_GET(rsp->fpma_to_portid);
	fcf_info->login = FW_FCOE_FCF_CMD_LOGIN_GET(rsp->fpma_to_portid);
	fcf_info->portid = FW_FCOE_FCF_CMD_PORTID_GET(rsp->fpma_to_portid);
	memcpy(fcf_info->fc_map, rsp->fc_map, sizeof(fcf_info->fc_map));
	memcpy(fcf_info->mac, rsp->mac, sizeof(fcf_info->mac));
	memcpy(fcf_info->name_id, rsp->name_id, sizeof(fcf_info->name_id));
	memcpy(fcf_info->fabric, rsp->fabric, sizeof(fcf_info->fabric));
	memcpy(fcf_info->spma_mac, rsp->spma_mac, sizeof(fcf_info->spma_mac));

	spin_unlock_irq(&hw->lock);

	mempool_free(mbp, hw->mb_mempool);
}