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
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {int /*<<< orphan*/  size; int /*<<< orphan*/ * val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GET_CFG ; 
 int /*<<< orphan*/  WID_ASSOC_RES_INFO ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wilc_get_vif_idx (struct wilc_vif*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 host_int_get_assoc_res_info(struct wilc_vif *vif,
				       u8 *assoc_resp_info,
				       u32 max_assoc_resp_info_len,
				       u32 *rcvd_assoc_resp_info_len)
{
	int result;
	struct wid wid;

	wid.id = WID_ASSOC_RES_INFO;
	wid.type = WID_STR;
	wid.val = assoc_resp_info;
	wid.size = max_assoc_resp_info_len;

	result = wilc_send_config_pkt(vif, GET_CFG, &wid, 1,
				      wilc_get_vif_idx(vif));
	if (result) {
		*rcvd_assoc_resp_info_len = 0;
		netdev_err(vif->ndev, "Failed to send association response\n");
		return -EINVAL;
	}

	*rcvd_assoc_resp_info_len = wid.size;
	return result;
}