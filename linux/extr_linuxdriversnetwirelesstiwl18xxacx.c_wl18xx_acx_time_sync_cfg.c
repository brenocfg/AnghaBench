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
struct TYPE_3__ {int /*<<< orphan*/ * params; } ;
struct TYPE_4__ {TYPE_1__ sg; } ;
struct wl1271 {int /*<<< orphan*/  zone_master_mac_addr; TYPE_2__ conf; } ;
struct acx_time_sync_cfg {int /*<<< orphan*/  zone_mac_addr; int /*<<< orphan*/  sync_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_TIME_SYNC_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t WL18XX_CONF_SG_TIME_SYNC ; 
 int /*<<< orphan*/  kfree (struct acx_time_sync_cfg*) ; 
 struct acx_time_sync_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_time_sync_cfg*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl18xx_acx_time_sync_cfg(struct wl1271 *wl)
{
	struct acx_time_sync_cfg *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx time sync cfg: mode %d, addr: %pM",
		     wl->conf.sg.params[WL18XX_CONF_SG_TIME_SYNC],
		     wl->zone_master_mac_addr);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->sync_mode = wl->conf.sg.params[WL18XX_CONF_SG_TIME_SYNC];
	memcpy(acx->zone_mac_addr, wl->zone_master_mac_addr, ETH_ALEN);

	ret = wl1271_cmd_configure(wl, ACX_TIME_SYNC_CFG,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx time sync cfg failed: %d", ret);
		goto out;
	}
out:
	kfree(acx);
	return ret;
}