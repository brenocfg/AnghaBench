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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ sg; } ;
struct wl1271 {TYPE_2__ conf; } ;
struct acx_bt_wlan_coex {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_SG_ENABLE ; 
 int /*<<< orphan*/  CONF_SG_DISABLE ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_bt_wlan_coex*) ; 
 struct acx_bt_wlan_coex* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_bt_wlan_coex*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_sg_enable(struct wl1271 *wl, bool enable)
{
	struct acx_bt_wlan_coex *pta;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx sg enable");

	pta = kzalloc(sizeof(*pta), GFP_KERNEL);
	if (!pta) {
		ret = -ENOMEM;
		goto out;
	}

	if (enable)
		pta->enable = wl->conf.sg.state;
	else
		pta->enable = CONF_SG_DISABLE;

	ret = wl1271_cmd_configure(wl, ACX_SG_ENABLE, pta, sizeof(*pta));
	if (ret < 0) {
		wl1271_warning("failed to set softgemini enable: %d", ret);
		goto out;
	}

out:
	kfree(pta);
	return ret;
}