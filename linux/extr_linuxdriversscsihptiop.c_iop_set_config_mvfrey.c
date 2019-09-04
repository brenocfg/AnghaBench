#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct hpt_iop_request_set_config* req_virt; } ;
struct TYPE_8__ {TYPE_2__ internal_req; } ;
struct TYPE_7__ {TYPE_4__ mvfrey; } ;
struct hptiop_hba {TYPE_3__ u; } ;
struct TYPE_5__ {scalar_t__ context_hi32; void* context; void* result; void* size; void* type; void* flags; } ;
struct hpt_iop_request_set_config {TYPE_1__ header; } ;

/* Variables and functions */
 int IOP_REQUEST_FLAG_OUTPUT_CONTEXT ; 
 int IOP_REQUEST_TYPE_SET_CONFIG ; 
 int IOP_RESULT_PENDING ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ iop_send_sync_request_mvfrey (struct hptiop_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct hpt_iop_request_set_config*,struct hpt_iop_request_set_config*,int) ; 

__attribute__((used)) static int iop_set_config_mvfrey(struct hptiop_hba *hba,
				struct hpt_iop_request_set_config *config)
{
	struct hpt_iop_request_set_config *req =
		hba->u.mvfrey.internal_req.req_virt;

	memcpy(req, config, sizeof(struct hpt_iop_request_set_config));
	req->header.flags = cpu_to_le32(IOP_REQUEST_FLAG_OUTPUT_CONTEXT);
	req->header.type = cpu_to_le32(IOP_REQUEST_TYPE_SET_CONFIG);
	req->header.size =
		cpu_to_le32(sizeof(struct hpt_iop_request_set_config));
	req->header.result = cpu_to_le32(IOP_RESULT_PENDING);
	req->header.context = cpu_to_le32(IOP_REQUEST_TYPE_SET_CONFIG<<5);
	req->header.context_hi32 = 0;

	if (iop_send_sync_request_mvfrey(hba, 0, 20000)) {
		dprintk("Set config send cmd failed\n");
		return -1;
	}

	return 0;
}