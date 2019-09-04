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
typedef  int /*<<< orphan*/  uint8_t ;
struct hwi_wrb_context {int /*<<< orphan*/  doorbell_offset; int /*<<< orphan*/  ulp_num; int /*<<< orphan*/  cid; } ;
struct TYPE_2__ {scalar_t__ dual_ulp_aware; } ;
struct beiscsi_hba {TYPE_1__ fw_config; } ;
struct be_wrbq_create_resp {int /*<<< orphan*/  doorbell_offset; int /*<<< orphan*/  ulp_num; int /*<<< orphan*/  cid; } ;
struct be_wrbq_create_req {int dua_feature; int /*<<< orphan*/  pages; int /*<<< orphan*/  ulp_num; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  hdr; } ;
struct be_queue_info {int created; int /*<<< orphan*/  id; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int /*<<< orphan*/  size; int /*<<< orphan*/  va; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  pdev; int /*<<< orphan*/  mbox_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BEISCSI_BIND_Q_TO_ULP_BIT ; 
 int BEISCSI_DUAL_ULP_AWARE_BIT ; 
 int /*<<< orphan*/  BEISCSI_ULP0 ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int /*<<< orphan*/  DB_TXULP0_OFFSET ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_WRBQ_CREATE ; 
 int /*<<< orphan*/  PAGES_4K_SPANNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_cmd_page_addrs_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_dma_mem*) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct beiscsi_hba* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int be_cmd_wrbq_create(struct be_ctrl_info *ctrl,
			struct be_dma_mem *q_mem,
			struct be_queue_info *wrbq,
			struct hwi_wrb_context *pwrb_context,
			uint8_t ulp_num)
{
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_wrbq_create_req *req = embedded_payload(wrb);
	struct be_wrbq_create_resp *resp = embedded_payload(wrb);
	struct beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	int status;

	mutex_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));

	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
		OPCODE_COMMON_ISCSI_WRBQ_CREATE, sizeof(*req));
	req->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);

	if (phba->fw_config.dual_ulp_aware) {
		req->ulp_num = ulp_num;
		req->dua_feature |= (1 << BEISCSI_DUAL_ULP_AWARE_BIT);
		req->dua_feature |= (1 << BEISCSI_BIND_Q_TO_ULP_BIT);
	}

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notify(ctrl);
	if (!status) {
		wrbq->id = le16_to_cpu(resp->cid);
		wrbq->created = true;

		pwrb_context->cid = wrbq->id;
		if (!phba->fw_config.dual_ulp_aware) {
			pwrb_context->doorbell_offset = DB_TXULP0_OFFSET;
			pwrb_context->ulp_num = BEISCSI_ULP0;
		} else {
			pwrb_context->ulp_num = resp->ulp_num;
			pwrb_context->doorbell_offset = resp->doorbell_offset;
		}
	}
	mutex_unlock(&ctrl->mbox_lock);
	return status;
}