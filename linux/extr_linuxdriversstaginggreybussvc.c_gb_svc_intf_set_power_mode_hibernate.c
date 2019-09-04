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
typedef  int u16 ;
struct gb_svc_intf_set_pwrm_response {int result_code; } ;
struct gb_svc_intf_set_pwrm_request {void* rx_mode; void* tx_mode; int /*<<< orphan*/  hs_series; int /*<<< orphan*/  intf_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int EIO ; 
 int GB_SVC_SETPWRM_PWR_OK ; 
 int /*<<< orphan*/  GB_SVC_TYPE_INTF_SET_PWRM ; 
 void* GB_SVC_UNIPRO_HIBERNATE_MODE ; 
 int /*<<< orphan*/  GB_SVC_UNIPRO_HS_SERIES_A ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_intf_set_pwrm_request*,int,struct gb_svc_intf_set_pwrm_response*,int) ; 
 int /*<<< orphan*/  memset (struct gb_svc_intf_set_pwrm_request*,int /*<<< orphan*/ ,int) ; 

int gb_svc_intf_set_power_mode_hibernate(struct gb_svc *svc, u8 intf_id)
{
	struct gb_svc_intf_set_pwrm_request request;
	struct gb_svc_intf_set_pwrm_response response;
	int ret;
	u16 result_code;

	memset(&request, 0, sizeof(request));

	request.intf_id = intf_id;
	request.hs_series = GB_SVC_UNIPRO_HS_SERIES_A;
	request.tx_mode = GB_SVC_UNIPRO_HIBERNATE_MODE;
	request.rx_mode = GB_SVC_UNIPRO_HIBERNATE_MODE;

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_INTF_SET_PWRM,
				&request, sizeof(request),
				&response, sizeof(response));
	if (ret < 0) {
		dev_err(&svc->dev,
			"failed to send set power mode operation to interface %u: %d\n",
			intf_id, ret);
		return ret;
	}

	result_code = response.result_code;
	if (result_code != GB_SVC_SETPWRM_PWR_OK) {
		dev_err(&svc->dev,
			"failed to hibernate the link for interface %u: %u\n",
			intf_id, result_code);
		return -EIO;
	}

	return 0;
}