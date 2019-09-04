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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct wilc_vif {int /*<<< orphan*/  ndev; struct host_if_drv* hif_drv; } ;
struct TYPE_2__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* conn_result ) (int /*<<< orphan*/ ,struct connect_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ies_len; scalar_t__ ies; scalar_t__ bssid; } ;
struct host_if_drv {int /*<<< orphan*/  hif_state; TYPE_1__ usr_conn_req; int /*<<< orphan*/  connect_timer; int /*<<< orphan*/  assoc_bssid; } ;
struct connect_info {scalar_t__ status; int /*<<< orphan*/ * req_ies; int /*<<< orphan*/ * resp_ies; int /*<<< orphan*/  req_ies_len; int /*<<< orphan*/  bssid; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_DISCONN_EVENT_CONN_RESP ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOST_IF_CONNECTED ; 
 int /*<<< orphan*/  HOST_IF_IDLE ; 
 int /*<<< orphan*/  MAC_STATUS_CONNECTED ; 
 int /*<<< orphan*/  MAC_STATUS_DISCONNECTED ; 
 int MAX_ASSOC_RESP_FRAME_SIZE ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_int_free_user_conn_req (struct host_if_drv*) ; 
 int /*<<< orphan*/  host_int_get_assoc_res_info (struct wilc_vif*,struct connect_info*,int,scalar_t__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct connect_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct connect_info* rcv_assoc_resp ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct connect_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_connected_ssid ; 
 int /*<<< orphan*/  wilc_during_ip_timer ; 
 int wilc_optaining_ip ; 
 scalar_t__ wilc_parse_assoc_resp_info (struct connect_info*,scalar_t__,struct connect_info*) ; 
 int /*<<< orphan*/  wilc_set_power_mgmt (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void host_int_parse_assoc_resp_info(struct wilc_vif *vif,
						  u8 mac_status)
{
	struct connect_info conn_info;
	struct host_if_drv *hif_drv = vif->hif_drv;

	memset(&conn_info, 0, sizeof(struct connect_info));

	if (mac_status == MAC_STATUS_CONNECTED) {
		u32 assoc_resp_info_len;

		memset(rcv_assoc_resp, 0, MAX_ASSOC_RESP_FRAME_SIZE);

		host_int_get_assoc_res_info(vif, rcv_assoc_resp,
					    MAX_ASSOC_RESP_FRAME_SIZE,
					    &assoc_resp_info_len);

		if (assoc_resp_info_len != 0) {
			s32 err = 0;

			err = wilc_parse_assoc_resp_info(rcv_assoc_resp,
							 assoc_resp_info_len,
							 &conn_info);
			if (err)
				netdev_err(vif->ndev,
					   "wilc_parse_assoc_resp_info() returned error %d\n",
					   err);
		}
	}

	if (mac_status == MAC_STATUS_CONNECTED &&
	    conn_info.status != WLAN_STATUS_SUCCESS) {
		netdev_err(vif->ndev,
			   "Received MAC status is MAC_STATUS_CONNECTED, Assoc Resp is not SUCCESS\n");
		eth_zero_addr(wilc_connected_ssid);
	} else if (mac_status == MAC_STATUS_DISCONNECTED)    {
		netdev_err(vif->ndev, "Received MAC status is MAC_STATUS_DISCONNECTED\n");
		eth_zero_addr(wilc_connected_ssid);
	}

	if (hif_drv->usr_conn_req.bssid) {
		memcpy(conn_info.bssid, hif_drv->usr_conn_req.bssid, 6);

		if (mac_status == MAC_STATUS_CONNECTED &&
		    conn_info.status == WLAN_STATUS_SUCCESS) {
			memcpy(hif_drv->assoc_bssid,
			       hif_drv->usr_conn_req.bssid, ETH_ALEN);
		}
	}

	if (hif_drv->usr_conn_req.ies) {
		conn_info.req_ies = kmemdup(hif_drv->usr_conn_req.ies,
					    hif_drv->usr_conn_req.ies_len,
					    GFP_KERNEL);
		if (conn_info.req_ies)
			conn_info.req_ies_len = hif_drv->usr_conn_req.ies_len;
	}

	del_timer(&hif_drv->connect_timer);
	hif_drv->usr_conn_req.conn_result(CONN_DISCONN_EVENT_CONN_RESP,
					  &conn_info, mac_status, NULL,
					  hif_drv->usr_conn_req.arg);

	if (mac_status == MAC_STATUS_CONNECTED &&
	    conn_info.status == WLAN_STATUS_SUCCESS) {
		wilc_set_power_mgmt(vif, 0, 0);

		hif_drv->hif_state = HOST_IF_CONNECTED;

		wilc_optaining_ip = true;
		mod_timer(&wilc_during_ip_timer,
			  jiffies + msecs_to_jiffies(10000));
	} else {
		hif_drv->hif_state = HOST_IF_IDLE;
	}

	kfree(conn_info.resp_ies);
	conn_info.resp_ies = NULL;

	kfree(conn_info.req_ies);
	conn_info.req_ies = NULL;
	host_int_free_user_conn_req(hif_drv);
}