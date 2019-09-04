#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int phys_port; int eqid_count; int cqid_count; int* iscsi_icd_count; int dual_ulp_aware; int /*<<< orphan*/  ulp_supported; int /*<<< orphan*/ * iscsi_icd_start; int /*<<< orphan*/ * iscsi_cid_start; int /*<<< orphan*/ * iscsi_cid_count; int /*<<< orphan*/ * iscsi_chain_count; int /*<<< orphan*/ * iscsi_chain_start; } ;
struct beiscsi_hba {TYPE_3__ fw_config; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_fw_cfg {int phys_port; int eqid_count; int cqid_count; int function_mode; TYPE_2__* ulp; TYPE_1__* chain_icd; int /*<<< orphan*/  hdr; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mbox_mem; } ;
struct TYPE_5__ {int ulp_mode; int icd_count; int /*<<< orphan*/  icd_base; int /*<<< orphan*/  sq_count; int /*<<< orphan*/  sq_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  chain_count; int /*<<< orphan*/  chain_base; } ;

/* Variables and functions */
 int BEISCSI_FUNC_DUA_MODE ; 
 int BEISCSI_GET_CID_COUNT (struct beiscsi_hba*,size_t) ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int BEISCSI_PHYS_PORT_MAX ; 
 size_t BEISCSI_ULP0 ; 
 size_t BEISCSI_ULP1 ; 
 size_t BEISCSI_ULP_COUNT ; 
 int BEISCSI_ULP_ISCSI_INI_MODE ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EINVAL ; 
 int /*<<< orphan*/  EMBED_MBX_MAX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OPCODE_COMMON_QUERY_FIRMWARE_CONFIG ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct be_fw_cfg* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  is_chip_be2_be3r (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int beiscsi_get_fw_config(struct be_ctrl_info *ctrl,
			  struct beiscsi_hba *phba)
{
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_fw_cfg *pfw_cfg = embedded_payload(wrb);
	uint32_t cid_count, icd_count;
	int status = -EINVAL;
	uint8_t ulp_num = 0;

	mutex_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));
	be_wrb_hdr_prepare(wrb, sizeof(*pfw_cfg), true, 0);

	be_cmd_hdr_prepare(&pfw_cfg->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_QUERY_FIRMWARE_CONFIG,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);

	if (be_mbox_notify(ctrl)) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : Failed in beiscsi_get_fw_config\n");
		goto fail_init;
	}

	/* FW response formats depend on port id */
	phba->fw_config.phys_port = pfw_cfg->phys_port;
	if (phba->fw_config.phys_port >= BEISCSI_PHYS_PORT_MAX) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : invalid physical port id %d\n",
			    phba->fw_config.phys_port);
		goto fail_init;
	}

	/* populate and check FW config against min and max values */
	if (!is_chip_be2_be3r(phba)) {
		phba->fw_config.eqid_count = pfw_cfg->eqid_count;
		phba->fw_config.cqid_count = pfw_cfg->cqid_count;
		if (phba->fw_config.eqid_count == 0 ||
		    phba->fw_config.eqid_count > 2048) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BG_%d : invalid EQ count %d\n",
				    phba->fw_config.eqid_count);
			goto fail_init;
		}
		if (phba->fw_config.cqid_count == 0 ||
		    phba->fw_config.cqid_count > 4096) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BG_%d : invalid CQ count %d\n",
				    phba->fw_config.cqid_count);
			goto fail_init;
		}
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : EQ_Count : %d CQ_Count : %d\n",
			    phba->fw_config.eqid_count,
			    phba->fw_config.cqid_count);
	}

	/**
	 * Check on which all ULP iSCSI Protocol is loaded.
	 * Set the Bit for those ULP. This set flag is used
	 * at all places in the code to check on which ULP
	 * iSCSi Protocol is loaded
	 **/
	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		if (pfw_cfg->ulp[ulp_num].ulp_mode &
		    BEISCSI_ULP_ISCSI_INI_MODE) {
			set_bit(ulp_num, &phba->fw_config.ulp_supported);

			/* Get the CID, ICD and Chain count for each ULP */
			phba->fw_config.iscsi_cid_start[ulp_num] =
				pfw_cfg->ulp[ulp_num].sq_base;
			phba->fw_config.iscsi_cid_count[ulp_num] =
				pfw_cfg->ulp[ulp_num].sq_count;

			phba->fw_config.iscsi_icd_start[ulp_num] =
				pfw_cfg->ulp[ulp_num].icd_base;
			phba->fw_config.iscsi_icd_count[ulp_num] =
				pfw_cfg->ulp[ulp_num].icd_count;

			phba->fw_config.iscsi_chain_start[ulp_num] =
				pfw_cfg->chain_icd[ulp_num].chain_base;
			phba->fw_config.iscsi_chain_count[ulp_num] =
				pfw_cfg->chain_icd[ulp_num].chain_count;

			beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
				    "BG_%d : Function loaded on ULP : %d\n"
				    "\tiscsi_cid_count : %d\n"
				    "\tiscsi_cid_start : %d\n"
				    "\t iscsi_icd_count : %d\n"
				    "\t iscsi_icd_start : %d\n",
				    ulp_num,
				    phba->fw_config.
				    iscsi_cid_count[ulp_num],
				    phba->fw_config.
				    iscsi_cid_start[ulp_num],
				    phba->fw_config.
				    iscsi_icd_count[ulp_num],
				    phba->fw_config.
				    iscsi_icd_start[ulp_num]);
		}
	}

	if (phba->fw_config.ulp_supported == 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : iSCSI initiator mode not set: ULP0 %x ULP1 %x\n",
			    pfw_cfg->ulp[BEISCSI_ULP0].ulp_mode,
			    pfw_cfg->ulp[BEISCSI_ULP1].ulp_mode);
		goto fail_init;
	}

	/**
	 * ICD is shared among ULPs. Use icd_count of any one loaded ULP
	 **/
	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++)
		if (test_bit(ulp_num, &phba->fw_config.ulp_supported))
			break;
	icd_count = phba->fw_config.iscsi_icd_count[ulp_num];
	if (icd_count == 0 || icd_count > 65536) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d: invalid ICD count %d\n", icd_count);
		goto fail_init;
	}

	cid_count = BEISCSI_GET_CID_COUNT(phba, BEISCSI_ULP0) +
		    BEISCSI_GET_CID_COUNT(phba, BEISCSI_ULP1);
	if (cid_count == 0 || cid_count > 4096) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d: invalid CID count %d\n", cid_count);
		goto fail_init;
	}

	/**
	 * Check FW is dual ULP aware i.e. can handle either
	 * of the protocols.
	 */
	phba->fw_config.dual_ulp_aware = (pfw_cfg->function_mode &
					  BEISCSI_FUNC_DUA_MODE);

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BG_%d : DUA Mode : 0x%x\n",
		    phba->fw_config.dual_ulp_aware);

	/* all set, continue using this FW config */
	status = 0;
fail_init:
	mutex_unlock(&ctrl->mbox_lock);
	return status;
}