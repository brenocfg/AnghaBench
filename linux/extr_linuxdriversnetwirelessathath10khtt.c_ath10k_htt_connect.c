#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath10k_htt {int /*<<< orphan*/  eid; TYPE_1__* ar; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep_rx_complete; int /*<<< orphan*/  ep_tx_complete; } ;
struct ath10k_htc_svc_conn_resp {int /*<<< orphan*/  eid; int /*<<< orphan*/  service_id; TYPE_2__ ep_ops; } ;
struct ath10k_htc_svc_conn_req {int /*<<< orphan*/  eid; int /*<<< orphan*/  service_id; TYPE_2__ ep_ops; } ;
typedef  int /*<<< orphan*/  conn_resp ;
typedef  int /*<<< orphan*/  conn_req ;
struct TYPE_3__ {int /*<<< orphan*/  htc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_HTC_SVC_ID_HTT_DATA_MSG ; 
 int ath10k_htc_connect_service (int /*<<< orphan*/ *,struct ath10k_htc_svc_conn_resp*,struct ath10k_htc_svc_conn_resp*) ; 
 int /*<<< orphan*/  ath10k_htt_htc_t2h_msg_handler ; 
 int /*<<< orphan*/  ath10k_htt_htc_tx_complete ; 
 int /*<<< orphan*/  memset (struct ath10k_htc_svc_conn_resp*,int /*<<< orphan*/ ,int) ; 

int ath10k_htt_connect(struct ath10k_htt *htt)
{
	struct ath10k_htc_svc_conn_req conn_req;
	struct ath10k_htc_svc_conn_resp conn_resp;
	int status;

	memset(&conn_req, 0, sizeof(conn_req));
	memset(&conn_resp, 0, sizeof(conn_resp));

	conn_req.ep_ops.ep_tx_complete = ath10k_htt_htc_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath10k_htt_htc_t2h_msg_handler;

	/* connect to control service */
	conn_req.service_id = ATH10K_HTC_SVC_ID_HTT_DATA_MSG;

	status = ath10k_htc_connect_service(&htt->ar->htc, &conn_req,
					    &conn_resp);

	if (status)
		return status;

	htt->eid = conn_resp.eid;

	return 0;
}