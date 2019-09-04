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
struct TYPE_4__ {int /*<<< orphan*/  wqe_com; } ;
struct TYPE_6__ {int /*<<< orphan*/  wqe_com; int /*<<< orphan*/  payload_offset_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  wqe_com; } ;
union lpfc_wqe128 {TYPE_1__ fcp_trsp; TYPE_3__ fcp_treceive; TYPE_2__ fcp_tsend; } ;

/* Variables and functions */
 int CLASS3 ; 
 int CMD_FCP_TRECEIVE64_WQE ; 
 int CMD_FCP_TRSP64_WQE ; 
 int CMD_FCP_TSEND64_WQE ; 
 int FCP_COMMAND_TRECEIVE ; 
 int FCP_COMMAND_TRSP ; 
 int FCP_COMMAND_TSEND ; 
 int LPFC_WQE_CQ_ID_DEFAULT ; 
 int LPFC_WQE_IOD_NONE ; 
 int LPFC_WQE_IOD_READ ; 
 int LPFC_WQE_IOD_WRITE ; 
 int LPFC_WQE_LENLOC_WORD12 ; 
 int LPFC_WQE_LENLOC_WORD3 ; 
 int PARM_REL_OFF ; 
 int PARM_UNUSED ; 
 int SLI4_CT_RPI ; 
 int /*<<< orphan*/  TXRDY_PAYLOAD_LEN ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 union lpfc_wqe128 lpfc_treceive_cmd_template ; 
 union lpfc_wqe128 lpfc_trsp_cmd_template ; 
 union lpfc_wqe128 lpfc_tsend_cmd_template ; 
 int /*<<< orphan*/  memset (union lpfc_wqe128*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wqe_ag ; 
 int /*<<< orphan*/  wqe_ar ; 
 int /*<<< orphan*/  wqe_class ; 
 int /*<<< orphan*/  wqe_cmd_type ; 
 int /*<<< orphan*/  wqe_cmnd ; 
 int /*<<< orphan*/  wqe_cqid ; 
 int /*<<< orphan*/  wqe_ct ; 
 int /*<<< orphan*/  wqe_dbde ; 
 int /*<<< orphan*/  wqe_iod ; 
 int /*<<< orphan*/  wqe_irsp ; 
 int /*<<< orphan*/  wqe_irsplen ; 
 int /*<<< orphan*/  wqe_lenloc ; 
 int /*<<< orphan*/  wqe_nvme ; 
 int /*<<< orphan*/  wqe_pbde ; 
 int /*<<< orphan*/  wqe_pu ; 
 int /*<<< orphan*/  wqe_sup ; 
 int /*<<< orphan*/  wqe_wqes ; 
 int /*<<< orphan*/  wqe_xc ; 

void
lpfc_nvmet_cmd_template(void)
{
	union lpfc_wqe128 *wqe;

	/* TSEND template */
	wqe = &lpfc_tsend_cmd_template;
	memset(wqe, 0, sizeof(union lpfc_wqe128));

	/* Word 0, 1, 2 - BDE is variable */

	/* Word 3 - payload_offset_len is zero */

	/* Word 4 - relative_offset is variable */

	/* Word 5 - is zero */

	/* Word 6 - ctxt_tag, xri_tag is variable */

	/* Word 7 - wqe_ar is variable */
	bf_set(wqe_cmnd, &wqe->fcp_tsend.wqe_com, CMD_FCP_TSEND64_WQE);
	bf_set(wqe_pu, &wqe->fcp_tsend.wqe_com, PARM_REL_OFF);
	bf_set(wqe_class, &wqe->fcp_tsend.wqe_com, CLASS3);
	bf_set(wqe_ct, &wqe->fcp_tsend.wqe_com, SLI4_CT_RPI);
	bf_set(wqe_ar, &wqe->fcp_tsend.wqe_com, 1);

	/* Word 8 - abort_tag is variable */

	/* Word 9  - reqtag, rcvoxid is variable */

	/* Word 10 - wqes, xc is variable */
	bf_set(wqe_nvme, &wqe->fcp_tsend.wqe_com, 1);
	bf_set(wqe_dbde, &wqe->fcp_tsend.wqe_com, 1);
	bf_set(wqe_wqes, &wqe->fcp_tsend.wqe_com, 0);
	bf_set(wqe_xc, &wqe->fcp_tsend.wqe_com, 1);
	bf_set(wqe_iod, &wqe->fcp_tsend.wqe_com, LPFC_WQE_IOD_WRITE);
	bf_set(wqe_lenloc, &wqe->fcp_tsend.wqe_com, LPFC_WQE_LENLOC_WORD12);

	/* Word 11 - sup, irsp, irsplen is variable */
	bf_set(wqe_cmd_type, &wqe->fcp_tsend.wqe_com, FCP_COMMAND_TSEND);
	bf_set(wqe_cqid, &wqe->fcp_tsend.wqe_com, LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_sup, &wqe->fcp_tsend.wqe_com, 0);
	bf_set(wqe_irsp, &wqe->fcp_tsend.wqe_com, 0);
	bf_set(wqe_irsplen, &wqe->fcp_tsend.wqe_com, 0);
	bf_set(wqe_pbde, &wqe->fcp_tsend.wqe_com, 0);

	/* Word 12 - fcp_data_len is variable */

	/* Word 13, 14, 15 - PBDE is zero */

	/* TRECEIVE template */
	wqe = &lpfc_treceive_cmd_template;
	memset(wqe, 0, sizeof(union lpfc_wqe128));

	/* Word 0, 1, 2 - BDE is variable */

	/* Word 3 */
	wqe->fcp_treceive.payload_offset_len = TXRDY_PAYLOAD_LEN;

	/* Word 4 - relative_offset is variable */

	/* Word 5 - is zero */

	/* Word 6 - ctxt_tag, xri_tag is variable */

	/* Word 7 */
	bf_set(wqe_cmnd, &wqe->fcp_treceive.wqe_com, CMD_FCP_TRECEIVE64_WQE);
	bf_set(wqe_pu, &wqe->fcp_treceive.wqe_com, PARM_REL_OFF);
	bf_set(wqe_class, &wqe->fcp_treceive.wqe_com, CLASS3);
	bf_set(wqe_ct, &wqe->fcp_treceive.wqe_com, SLI4_CT_RPI);
	bf_set(wqe_ar, &wqe->fcp_treceive.wqe_com, 0);

	/* Word 8 - abort_tag is variable */

	/* Word 9  - reqtag, rcvoxid is variable */

	/* Word 10 - xc is variable */
	bf_set(wqe_dbde, &wqe->fcp_treceive.wqe_com, 1);
	bf_set(wqe_wqes, &wqe->fcp_treceive.wqe_com, 0);
	bf_set(wqe_nvme, &wqe->fcp_treceive.wqe_com, 1);
	bf_set(wqe_iod, &wqe->fcp_treceive.wqe_com, LPFC_WQE_IOD_READ);
	bf_set(wqe_lenloc, &wqe->fcp_treceive.wqe_com, LPFC_WQE_LENLOC_WORD12);
	bf_set(wqe_xc, &wqe->fcp_tsend.wqe_com, 1);

	/* Word 11 - pbde is variable */
	bf_set(wqe_cmd_type, &wqe->fcp_treceive.wqe_com, FCP_COMMAND_TRECEIVE);
	bf_set(wqe_cqid, &wqe->fcp_treceive.wqe_com, LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_sup, &wqe->fcp_treceive.wqe_com, 0);
	bf_set(wqe_irsp, &wqe->fcp_treceive.wqe_com, 0);
	bf_set(wqe_irsplen, &wqe->fcp_treceive.wqe_com, 0);
	bf_set(wqe_pbde, &wqe->fcp_treceive.wqe_com, 1);

	/* Word 12 - fcp_data_len is variable */

	/* Word 13, 14, 15 - PBDE is variable */

	/* TRSP template */
	wqe = &lpfc_trsp_cmd_template;
	memset(wqe, 0, sizeof(union lpfc_wqe128));

	/* Word 0, 1, 2 - BDE is variable */

	/* Word 3 - response_len is variable */

	/* Word 4, 5 - is zero */

	/* Word 6 - ctxt_tag, xri_tag is variable */

	/* Word 7 */
	bf_set(wqe_cmnd, &wqe->fcp_trsp.wqe_com, CMD_FCP_TRSP64_WQE);
	bf_set(wqe_pu, &wqe->fcp_trsp.wqe_com, PARM_UNUSED);
	bf_set(wqe_class, &wqe->fcp_trsp.wqe_com, CLASS3);
	bf_set(wqe_ct, &wqe->fcp_trsp.wqe_com, SLI4_CT_RPI);
	bf_set(wqe_ag, &wqe->fcp_trsp.wqe_com, 1); /* wqe_ar */

	/* Word 8 - abort_tag is variable */

	/* Word 9  - reqtag is variable */

	/* Word 10 wqes, xc is variable */
	bf_set(wqe_dbde, &wqe->fcp_trsp.wqe_com, 1);
	bf_set(wqe_nvme, &wqe->fcp_trsp.wqe_com, 1);
	bf_set(wqe_wqes, &wqe->fcp_trsp.wqe_com, 0);
	bf_set(wqe_xc, &wqe->fcp_trsp.wqe_com, 0);
	bf_set(wqe_iod, &wqe->fcp_trsp.wqe_com, LPFC_WQE_IOD_NONE);
	bf_set(wqe_lenloc, &wqe->fcp_trsp.wqe_com, LPFC_WQE_LENLOC_WORD3);

	/* Word 11 irsp, irsplen is variable */
	bf_set(wqe_cmd_type, &wqe->fcp_trsp.wqe_com, FCP_COMMAND_TRSP);
	bf_set(wqe_cqid, &wqe->fcp_trsp.wqe_com, LPFC_WQE_CQ_ID_DEFAULT);
	bf_set(wqe_sup, &wqe->fcp_trsp.wqe_com, 0);
	bf_set(wqe_irsp, &wqe->fcp_trsp.wqe_com, 0);
	bf_set(wqe_irsplen, &wqe->fcp_trsp.wqe_com, 0);
	bf_set(wqe_pbde, &wqe->fcp_trsp.wqe_com, 0);

	/* Word 12, 13, 14, 15 - is zero */
}