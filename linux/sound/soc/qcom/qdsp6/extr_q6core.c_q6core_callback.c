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
struct q6core {int get_version_supported; int resp_received; int fwk_version_supported; int get_state_supported; int /*<<< orphan*/  wait; int /*<<< orphan*/  avcs_state; void* svc_version; void* fwk_version; } ;
struct avcs_cmdrsp_get_version {int /*<<< orphan*/  opcode; int /*<<< orphan*/  num_services; int /*<<< orphan*/  status; } ;
struct avcs_cmdrsp_get_fwk_version {int /*<<< orphan*/  opcode; int /*<<< orphan*/  num_services; int /*<<< orphan*/  status; } ;
struct aprv2_ibasic_rsp_result_t {int /*<<< orphan*/  opcode; int /*<<< orphan*/  num_services; int /*<<< orphan*/  status; } ;
struct apr_hdr {int opcode; } ;
struct apr_resp_pkt {struct avcs_cmdrsp_get_version* payload; struct apr_hdr hdr; } ;
struct apr_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADSP_EUNSUPPORTED ; 
#define  APR_BASIC_RSP_RESULT 134 
#define  AVCS_CMDRSP_ADSP_EVENT_GET_STATE 133 
#define  AVCS_CMDRSP_GET_FWK_VERSION 132 
#define  AVCS_CMD_ADSP_EVENT_GET_STATE 131 
#define  AVCS_CMD_GET_FWK_VERSION 130 
#define  AVCS_GET_VERSIONS 129 
#define  AVCS_GET_VERSIONS_RSP 128 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct q6core* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 void* kmemdup (struct avcs_cmdrsp_get_version*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct avcs_cmdrsp_get_version*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_api_info ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6core_callback(struct apr_device *adev, struct apr_resp_pkt *data)
{
	struct q6core *core = dev_get_drvdata(&adev->dev);
	struct aprv2_ibasic_rsp_result_t *result;
	struct apr_hdr *hdr = &data->hdr;

	result = data->payload;
	switch (hdr->opcode) {
	case APR_BASIC_RSP_RESULT:{
		result = data->payload;
		switch (result->opcode) {
		case AVCS_GET_VERSIONS:
			if (result->status == ADSP_EUNSUPPORTED)
				core->get_version_supported = false;
			core->resp_received = true;
			break;
		case AVCS_CMD_GET_FWK_VERSION:
			if (result->status == ADSP_EUNSUPPORTED)
				core->fwk_version_supported = false;
			core->resp_received = true;
			break;
		case AVCS_CMD_ADSP_EVENT_GET_STATE:
			if (result->status == ADSP_EUNSUPPORTED)
				core->get_state_supported = false;
			core->resp_received = true;
			break;
		}
		break;
	}
	case AVCS_CMDRSP_GET_FWK_VERSION: {
		struct avcs_cmdrsp_get_fwk_version *fwk;

		fwk = data->payload;

		core->fwk_version = kmemdup(data->payload,
					    struct_size(fwk, svc_api_info,
							fwk->num_services),
					    GFP_ATOMIC);
		if (!core->fwk_version)
			return -ENOMEM;

		core->fwk_version_supported = true;
		core->resp_received = true;

		break;
	}
	case AVCS_GET_VERSIONS_RSP: {
		struct avcs_cmdrsp_get_version *v;

		v = data->payload;

		core->svc_version = kmemdup(data->payload,
					    struct_size(v, svc_api_info,
							v->num_services),
					    GFP_ATOMIC);
		if (!core->svc_version)
			return -ENOMEM;

		core->get_version_supported = true;
		core->resp_received = true;

		break;
	}
	case AVCS_CMDRSP_ADSP_EVENT_GET_STATE:
		core->get_state_supported = true;
		core->avcs_state = result->opcode;

		core->resp_received = true;
		break;
	default:
		dev_err(&adev->dev, "Message id from adsp core svc: 0x%x\n",
			hdr->opcode);
		break;
	}

	if (core->resp_received)
		wake_up(&core->wait);

	return 0;
}