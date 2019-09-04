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
struct gb_control_bundle_pm_response {int status; } ;
struct gb_control_bundle_pm_request {int /*<<< orphan*/  bundle_id; } ;
struct gb_control {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int GB_CONTROL_BUNDLE_PM_OK ; 
 int /*<<< orphan*/  GB_CONTROL_TYPE_BUNDLE_SUSPEND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int gb_control_bundle_pm_status_map (int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_control_bundle_pm_request*,int,struct gb_control_bundle_pm_response*,int) ; 

int gb_control_bundle_suspend(struct gb_control *control, u8 bundle_id)
{
	struct gb_control_bundle_pm_request request;
	struct gb_control_bundle_pm_response response;
	int ret;

	request.bundle_id = bundle_id;
	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_BUNDLE_SUSPEND, &request,
				sizeof(request), &response, sizeof(response));
	if (ret) {
		dev_err(&control->dev, "failed to send bundle %u suspend: %d\n",
			bundle_id, ret);
		return ret;
	}

	if (response.status != GB_CONTROL_BUNDLE_PM_OK) {
		dev_err(&control->dev, "failed to suspend bundle %u: %d\n",
			bundle_id, response.status);
		return gb_control_bundle_pm_status_map(response.status);
	}

	return 0;
}