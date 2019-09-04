#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_sli4_parameters {scalar_t__ sge_supp_len; } ;
struct lpfc_sli4_cfg_mhdr {int dummy; } ;
struct lpfc_pc_sli4_params {int if_type; int sli_rev; int sli_family; int featurelevel_1; int featurelevel_2; scalar_t__ sge_supp_len; int loopbk_scope; int oas_supported; int cqv; int mqv; int wqv; int rqv; int eqav; int cqav; int wqsize; int bv1s; int sgl_pages_max; int wqpcnt; int sgl_pp_align; } ;
struct TYPE_13__ {struct lpfc_sli4_parameters sli4_parameters; } ;
struct TYPE_14__ {TYPE_2__ get_sli4_parameters; } ;
struct lpfc_mqe {TYPE_3__ un; } ;
struct lpfc_mbx_get_sli4_parameters {int dummy; } ;
struct TYPE_15__ {int rpi_hdrs_in_use; int extents_in_use; struct lpfc_sli4_parameters sli_intf; struct lpfc_pc_sli4_params pc_sli4_params; int /*<<< orphan*/  intr_enable; } ;
struct TYPE_16__ {int /*<<< orphan*/  sli_flag; } ;
struct lpfc_hba {int nvme_support; int cfg_enable_fc4_type; int fcp_embed_io; int enab_exp_wqcq_pages; int mds_diags_support; TYPE_4__ sli4_hba; int /*<<< orphan*/  cfg_suppress_rsp; int /*<<< orphan*/  cfg_nvme_embed_cmd; scalar_t__ cfg_enable_pbde; TYPE_5__ sli; int /*<<< orphan*/  cfg_fcp_io_channel; int /*<<< orphan*/  io_channel_irqs; scalar_t__ cfg_nvme_io_channel; int /*<<< orphan*/  cfg_nvmet_mrq; scalar_t__ nvmet_support; int /*<<< orphan*/  sli3_options; } ;
struct TYPE_12__ {struct lpfc_mqe mqe; } ;
struct TYPE_17__ {TYPE_1__ u; } ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_INIT ; 
 int LOG_NVME ; 
 int LPFC_CQ_16K_PAGE_SZ ; 
 int LPFC_ENABLE_FCP ; 
 scalar_t__ LPFC_MAX_SGE_SIZE ; 
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_GET_SLI4_PARAMETERS ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  LPFC_NVMET_MRQ_OFF ; 
 int /*<<< orphan*/  LPFC_SLI4_MBX_EMBED ; 
 int /*<<< orphan*/  LPFC_SLI4_PHWQ_ENABLED ; 
 int LPFC_SLI_INTF_FAMILY_LNCR_A0 ; 
 int LPFC_SLI_INTF_IF_TYPE_2 ; 
 int LPFC_SLI_INTF_IF_TYPE_6 ; 
 int /*<<< orphan*/  LPFC_SLI_SUPPRESS_RSP ; 
 int /*<<< orphan*/  LPFC_SLI_USE_EQDR ; 
 int LPFC_WQ_16K_PAGE_SZ ; 
 int LPFC_WQ_SZ128_SUPPORT ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_sli4_parameters*) ; 
 int /*<<< orphan*/  cfg_bv1s ; 
 int /*<<< orphan*/  cfg_cqav ; 
 int /*<<< orphan*/  cfg_cqpsize ; 
 int /*<<< orphan*/  cfg_cqv ; 
 int /*<<< orphan*/  cfg_eqav ; 
 int /*<<< orphan*/  cfg_eqdr ; 
 int /*<<< orphan*/  cfg_ext ; 
 int /*<<< orphan*/  cfg_ext_embed_cb ; 
 int /*<<< orphan*/  cfg_hdrr ; 
 int /*<<< orphan*/  cfg_if_type ; 
 int /*<<< orphan*/  cfg_mds_diags ; 
 int /*<<< orphan*/  cfg_mqv ; 
 int /*<<< orphan*/  cfg_nosr ; 
 int /*<<< orphan*/  cfg_nvme ; 
 int /*<<< orphan*/  cfg_oas ; 
 int /*<<< orphan*/  cfg_phwq ; 
 int /*<<< orphan*/  cfg_rqv ; 
 int /*<<< orphan*/  cfg_sgl_page_cnt ; 
 int /*<<< orphan*/  cfg_sgl_pp_align ; 
 int /*<<< orphan*/  cfg_sli_family ; 
 int /*<<< orphan*/  cfg_sli_hint_1 ; 
 int /*<<< orphan*/  cfg_sli_hint_2 ; 
 int /*<<< orphan*/  cfg_sli_rev ; 
 int /*<<< orphan*/  cfg_wqpcnt ; 
 int /*<<< orphan*/  cfg_wqpsize ; 
 int /*<<< orphan*/  cfg_wqsize ; 
 int /*<<< orphan*/  cfg_wqv ; 
 int /*<<< orphan*/  cfg_xib ; 
 int /*<<< orphan*/  loopbk_scope ; 
 int /*<<< orphan*/  lpfc_mbox_tmo_val (struct lpfc_hba*,TYPE_6__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int,int,...) ; 
 int /*<<< orphan*/  lpfc_sli4_config (struct lpfc_hba*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_sli_intf_sli_family ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox_wait (struct lpfc_hba*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int
lpfc_get_sli4_parameters(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	int rc;
	struct lpfc_mqe *mqe = &mboxq->u.mqe;
	struct lpfc_pc_sli4_params *sli4_params;
	uint32_t mbox_tmo;
	int length;
	bool exp_wqcq_pages = true;
	struct lpfc_sli4_parameters *mbx_sli4_parameters;

	/*
	 * By default, the driver assumes the SLI4 port requires RPI
	 * header postings.  The SLI4_PARAM response will correct this
	 * assumption.
	 */
	phba->sli4_hba.rpi_hdrs_in_use = 1;

	/* Read the port's SLI4 Config Parameters */
	length = (sizeof(struct lpfc_mbx_get_sli4_parameters) -
		  sizeof(struct lpfc_sli4_cfg_mhdr));
	lpfc_sli4_config(phba, mboxq, LPFC_MBOX_SUBSYSTEM_COMMON,
			 LPFC_MBOX_OPCODE_GET_SLI4_PARAMETERS,
			 length, LPFC_SLI4_MBX_EMBED);
	if (!phba->sli4_hba.intr_enable)
		rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_POLL);
	else {
		mbox_tmo = lpfc_mbox_tmo_val(phba, mboxq);
		rc = lpfc_sli_issue_mbox_wait(phba, mboxq, mbox_tmo);
	}
	if (unlikely(rc))
		return rc;
	sli4_params = &phba->sli4_hba.pc_sli4_params;
	mbx_sli4_parameters = &mqe->un.get_sli4_parameters.sli4_parameters;
	sli4_params->if_type = bf_get(cfg_if_type, mbx_sli4_parameters);
	sli4_params->sli_rev = bf_get(cfg_sli_rev, mbx_sli4_parameters);
	sli4_params->sli_family = bf_get(cfg_sli_family, mbx_sli4_parameters);
	sli4_params->featurelevel_1 = bf_get(cfg_sli_hint_1,
					     mbx_sli4_parameters);
	sli4_params->featurelevel_2 = bf_get(cfg_sli_hint_2,
					     mbx_sli4_parameters);
	if (bf_get(cfg_phwq, mbx_sli4_parameters))
		phba->sli3_options |= LPFC_SLI4_PHWQ_ENABLED;
	else
		phba->sli3_options &= ~LPFC_SLI4_PHWQ_ENABLED;
	sli4_params->sge_supp_len = mbx_sli4_parameters->sge_supp_len;
	sli4_params->loopbk_scope = bf_get(loopbk_scope, mbx_sli4_parameters);
	sli4_params->oas_supported = bf_get(cfg_oas, mbx_sli4_parameters);
	sli4_params->cqv = bf_get(cfg_cqv, mbx_sli4_parameters);
	sli4_params->mqv = bf_get(cfg_mqv, mbx_sli4_parameters);
	sli4_params->wqv = bf_get(cfg_wqv, mbx_sli4_parameters);
	sli4_params->rqv = bf_get(cfg_rqv, mbx_sli4_parameters);
	sli4_params->eqav = bf_get(cfg_eqav, mbx_sli4_parameters);
	sli4_params->cqav = bf_get(cfg_cqav, mbx_sli4_parameters);
	sli4_params->wqsize = bf_get(cfg_wqsize, mbx_sli4_parameters);
	sli4_params->bv1s = bf_get(cfg_bv1s, mbx_sli4_parameters);
	sli4_params->sgl_pages_max = bf_get(cfg_sgl_page_cnt,
					    mbx_sli4_parameters);
	sli4_params->wqpcnt = bf_get(cfg_wqpcnt, mbx_sli4_parameters);
	sli4_params->sgl_pp_align = bf_get(cfg_sgl_pp_align,
					   mbx_sli4_parameters);
	phba->sli4_hba.extents_in_use = bf_get(cfg_ext, mbx_sli4_parameters);
	phba->sli4_hba.rpi_hdrs_in_use = bf_get(cfg_hdrr, mbx_sli4_parameters);
	phba->nvme_support = (bf_get(cfg_nvme, mbx_sli4_parameters) &&
			      bf_get(cfg_xib, mbx_sli4_parameters));

	if ((phba->cfg_enable_fc4_type == LPFC_ENABLE_FCP) ||
	    !phba->nvme_support) {
		phba->nvme_support = 0;
		phba->nvmet_support = 0;
		phba->cfg_nvmet_mrq = LPFC_NVMET_MRQ_OFF;
		phba->cfg_nvme_io_channel = 0;
		phba->io_channel_irqs = phba->cfg_fcp_io_channel;
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT | LOG_NVME,
				"6101 Disabling NVME support: "
				"Not supported by firmware: %d %d\n",
				bf_get(cfg_nvme, mbx_sli4_parameters),
				bf_get(cfg_xib, mbx_sli4_parameters));

		/* If firmware doesn't support NVME, just use SCSI support */
		if (!(phba->cfg_enable_fc4_type & LPFC_ENABLE_FCP))
			return -ENODEV;
		phba->cfg_enable_fc4_type = LPFC_ENABLE_FCP;
	}

	/* Only embed PBDE for if_type 6, PBDE support requires xib be set */
	if ((bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) !=
	    LPFC_SLI_INTF_IF_TYPE_6) || (!bf_get(cfg_xib, mbx_sli4_parameters)))
		phba->cfg_enable_pbde = 0;

	/*
	 * To support Suppress Response feature we must satisfy 3 conditions.
	 * lpfc_suppress_rsp module parameter must be set (default).
	 * In SLI4-Parameters Descriptor:
	 * Extended Inline Buffers (XIB) must be supported.
	 * Suppress Response IU Not Supported (SRIUNS) must NOT be supported
	 * (double negative).
	 */
	if (phba->cfg_suppress_rsp && bf_get(cfg_xib, mbx_sli4_parameters) &&
	    !(bf_get(cfg_nosr, mbx_sli4_parameters)))
		phba->sli.sli_flag |= LPFC_SLI_SUPPRESS_RSP;
	else
		phba->cfg_suppress_rsp = 0;

	if (bf_get(cfg_eqdr, mbx_sli4_parameters))
		phba->sli.sli_flag |= LPFC_SLI_USE_EQDR;

	/* Make sure that sge_supp_len can be handled by the driver */
	if (sli4_params->sge_supp_len > LPFC_MAX_SGE_SIZE)
		sli4_params->sge_supp_len = LPFC_MAX_SGE_SIZE;

	/*
	 * Check whether the adapter supports an embedded copy of the
	 * FCP CMD IU within the WQE for FCP_Ixxx commands. In order
	 * to use this option, 128-byte WQEs must be used.
	 */
	if (bf_get(cfg_ext_embed_cb, mbx_sli4_parameters))
		phba->fcp_embed_io = 1;
	else
		phba->fcp_embed_io = 0;

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT | LOG_NVME,
			"6422 XIB %d PBDE %d: FCP %d NVME %d %d %d\n",
			bf_get(cfg_xib, mbx_sli4_parameters),
			phba->cfg_enable_pbde,
			phba->fcp_embed_io, phba->nvme_support,
			phba->cfg_nvme_embed_cmd, phba->cfg_suppress_rsp);

	if ((bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) ==
	    LPFC_SLI_INTF_IF_TYPE_2) &&
	    (bf_get(lpfc_sli_intf_sli_family, &phba->sli4_hba.sli_intf) ==
		 LPFC_SLI_INTF_FAMILY_LNCR_A0))
		exp_wqcq_pages = false;

	if ((bf_get(cfg_cqpsize, mbx_sli4_parameters) & LPFC_CQ_16K_PAGE_SZ) &&
	    (bf_get(cfg_wqpsize, mbx_sli4_parameters) & LPFC_WQ_16K_PAGE_SZ) &&
	    exp_wqcq_pages &&
	    (sli4_params->wqsize & LPFC_WQ_SZ128_SUPPORT))
		phba->enab_exp_wqcq_pages = 1;
	else
		phba->enab_exp_wqcq_pages = 0;
	/*
	 * Check if the SLI port supports MDS Diagnostics
	 */
	if (bf_get(cfg_mds_diags, mbx_sli4_parameters))
		phba->mds_diags_support = 1;
	else
		phba->mds_diags_support = 0;
	return 0;
}