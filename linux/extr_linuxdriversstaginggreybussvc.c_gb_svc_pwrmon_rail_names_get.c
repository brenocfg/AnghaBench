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
struct gb_svc_pwrmon_rail_names_get_response {int status; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int GB_SVC_OP_SUCCESS ; 
 int /*<<< orphan*/  GB_SVC_TYPE_PWRMON_RAIL_NAMES_GET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_svc_pwrmon_rail_names_get_response*,size_t) ; 

__attribute__((used)) static int gb_svc_pwrmon_rail_names_get(struct gb_svc *svc,
		struct gb_svc_pwrmon_rail_names_get_response *response,
		size_t bufsize)
{
	int ret;

	ret = gb_operation_sync(svc->connection,
				GB_SVC_TYPE_PWRMON_RAIL_NAMES_GET, NULL, 0,
				response, bufsize);
	if (ret) {
		dev_err(&svc->dev, "failed to get rail names: %d\n", ret);
		return ret;
	}

	if (response->status != GB_SVC_OP_SUCCESS) {
		dev_err(&svc->dev,
			"SVC error while getting rail names: %u\n",
			response->status);
		return -EREMOTEIO;
	}

	return 0;
}