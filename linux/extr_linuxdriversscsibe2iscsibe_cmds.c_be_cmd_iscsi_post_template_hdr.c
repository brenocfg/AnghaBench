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
struct be_post_template_pages_req {int /*<<< orphan*/  pages; int /*<<< orphan*/  type; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  hdr; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int /*<<< orphan*/  size; int /*<<< orphan*/  va; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mbox_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BEISCSI_TEMPLATE_HDR_TYPE_ISCSI ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  OPCODE_COMMON_ADD_TEMPLATE_HEADER_BUFFERS ; 
 int /*<<< orphan*/  PAGES_4K_SPANNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_cmd_page_addrs_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_dma_mem*) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 struct be_post_template_pages_req* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int be_cmd_iscsi_post_template_hdr(struct be_ctrl_info *ctrl,
				    struct be_dma_mem *q_mem)
{
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_post_template_pages_req *req = embedded_payload(wrb);
	int status;

	mutex_lock(&ctrl->mbox_lock);

	memset(wrb, 0, sizeof(*wrb));
	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_ADD_TEMPLATE_HEADER_BUFFERS,
			   sizeof(*req));

	req->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	req->type = BEISCSI_TEMPLATE_HDR_TYPE_ISCSI;
	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notify(ctrl);
	mutex_unlock(&ctrl->mbox_lock);
	return status;
}