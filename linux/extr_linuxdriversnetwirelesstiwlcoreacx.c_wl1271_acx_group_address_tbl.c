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
typedef  int u32 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct acx_dot11_grp_addr_tbl {int enabled; int num_groups; int /*<<< orphan*/  mac_table; int /*<<< orphan*/  role_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DOT11_GROUP_ADDRESS_TBL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_dot11_grp_addr_tbl*) ; 
 struct acx_dot11_grp_addr_tbl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_dot11_grp_addr_tbl*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_group_address_tbl(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				 bool enable, void *mc_list, u32 mc_list_len)
{
	struct acx_dot11_grp_addr_tbl *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx group address tbl");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	/* MAC filtering */
	acx->role_id = wlvif->role_id;
	acx->enabled = enable;
	acx->num_groups = mc_list_len;
	memcpy(acx->mac_table, mc_list, mc_list_len * ETH_ALEN);

	ret = wl1271_cmd_configure(wl, DOT11_GROUP_ADDRESS_TBL,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("failed to set group addr table: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}