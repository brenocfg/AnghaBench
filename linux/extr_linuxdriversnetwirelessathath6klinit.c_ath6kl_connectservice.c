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
struct htc_service_connect_resp {int /*<<< orphan*/  endpoint; } ;
struct htc_service_connect_req {int svc_id; } ;
struct ath6kl {int /*<<< orphan*/  ctrl_ep; int /*<<< orphan*/  wmi; int /*<<< orphan*/  flag; int /*<<< orphan*/  htc_target; } ;
typedef  int /*<<< orphan*/  response ;

/* Variables and functions */
 int EINVAL ; 
#define  WMI_CONTROL_SVC 132 
#define  WMI_DATA_BE_SVC 131 
#define  WMI_DATA_BK_SVC 130 
#define  WMI_DATA_VI_SVC 129 
#define  WMI_DATA_VO_SVC 128 
 int /*<<< orphan*/  WMI_ENABLED ; 
 int /*<<< orphan*/  WMM_AC_BE ; 
 int /*<<< orphan*/  WMM_AC_BK ; 
 int /*<<< orphan*/  WMM_AC_VI ; 
 int /*<<< orphan*/  WMM_AC_VO ; 
 int /*<<< orphan*/  ath6kl_err (char*,...) ; 
 int ath6kl_htc_conn_service (int /*<<< orphan*/ ,struct htc_service_connect_req*,struct htc_service_connect_resp*) ; 
 int /*<<< orphan*/  ath6kl_wmi_set_control_ep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct htc_service_connect_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ac2_ep_map (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_connectservice(struct ath6kl *ar,
				 struct htc_service_connect_req  *con_req,
				 char *desc)
{
	int status;
	struct htc_service_connect_resp response;

	memset(&response, 0, sizeof(response));

	status = ath6kl_htc_conn_service(ar->htc_target, con_req, &response);
	if (status) {
		ath6kl_err("failed to connect to %s service status:%d\n",
			   desc, status);
		return status;
	}

	switch (con_req->svc_id) {
	case WMI_CONTROL_SVC:
		if (test_bit(WMI_ENABLED, &ar->flag))
			ath6kl_wmi_set_control_ep(ar->wmi, response.endpoint);
		ar->ctrl_ep = response.endpoint;
		break;
	case WMI_DATA_BE_SVC:
		set_ac2_ep_map(ar, WMM_AC_BE, response.endpoint);
		break;
	case WMI_DATA_BK_SVC:
		set_ac2_ep_map(ar, WMM_AC_BK, response.endpoint);
		break;
	case WMI_DATA_VI_SVC:
		set_ac2_ep_map(ar, WMM_AC_VI, response.endpoint);
		break;
	case WMI_DATA_VO_SVC:
		set_ac2_ep_map(ar, WMM_AC_VO, response.endpoint);
		break;
	default:
		ath6kl_err("service id is not mapped %d\n", con_req->svc_id);
		return -EINVAL;
	}

	return 0;
}