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
typedef  int /*<<< orphan*/  u8 ;
struct gb_svc_intf_resume_response {int status; } ;
struct gb_svc_intf_resume_request {int /*<<< orphan*/  intf_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int EREMOTEIO ; 
 int GB_SVC_OP_SUCCESS ; 
 int /*<<< orphan*/  GB_SVC_TYPE_INTF_RESUME ; 
 int /*<<< orphan*/  SVC_INTF_RESUME_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int gb_operation_sync_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_intf_resume_request*,int,struct gb_svc_intf_resume_response*,int,int /*<<< orphan*/ ) ; 

int gb_svc_intf_resume(struct gb_svc *svc, u8 intf_id)
{
	struct gb_svc_intf_resume_request request;
	struct gb_svc_intf_resume_response response;
	int ret;

	request.intf_id = intf_id;

	ret = gb_operation_sync_timeout(svc->connection,
					GB_SVC_TYPE_INTF_RESUME,
					&request, sizeof(request),
					&response, sizeof(response),
					SVC_INTF_RESUME_TIMEOUT);
	if (ret < 0) {
		dev_err(&svc->dev, "failed to send interface resume %u: %d\n",
			intf_id, ret);
		return ret;
	}

	if (response.status != GB_SVC_OP_SUCCESS) {
		dev_err(&svc->dev, "failed to resume interface %u: %u\n",
			intf_id, response.status);
		return -EREMOTEIO;
	}

	return 0;
}