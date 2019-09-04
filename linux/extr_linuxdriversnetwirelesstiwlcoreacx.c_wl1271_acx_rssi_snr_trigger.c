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
typedef  int /*<<< orphan*/  u8 ;
struct wl12xx_vif {int last_rssi_event; int /*<<< orphan*/  role_id; } ;
struct wl1271_acx_rssi_snr_trigger {int /*<<< orphan*/  hysteresis; void* threshold; int /*<<< orphan*/  dir; int /*<<< orphan*/  index; int /*<<< orphan*/  enable; int /*<<< orphan*/  type; int /*<<< orphan*/  metric; void* pacing; int /*<<< orphan*/  role_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  trigger_pacing; } ;
struct TYPE_4__ {TYPE_1__ roam_trigger; } ;
struct wl1271 {TYPE_2__ conf; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_RSSI_SNR_TRIGGER ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WL1271_ACX_TRIG_DIR_BIDIR ; 
 int /*<<< orphan*/  WL1271_ACX_TRIG_DISABLE ; 
 int /*<<< orphan*/  WL1271_ACX_TRIG_ENABLE ; 
 int /*<<< orphan*/  WL1271_ACX_TRIG_IDX_RSSI ; 
 int /*<<< orphan*/  WL1271_ACX_TRIG_METRIC_RSSI_BEACON ; 
 int /*<<< orphan*/  WL1271_ACX_TRIG_TYPE_EDGE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_rssi_snr_trigger*) ; 
 struct wl1271_acx_rssi_snr_trigger* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_rssi_snr_trigger*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_rssi_snr_trigger(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				bool enable, s16 thold, u8 hyst)
{
	struct wl1271_acx_rssi_snr_trigger *acx = NULL;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx rssi snr trigger");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	wlvif->last_rssi_event = -1;

	acx->role_id = wlvif->role_id;
	acx->pacing = cpu_to_le16(wl->conf.roam_trigger.trigger_pacing);
	acx->metric = WL1271_ACX_TRIG_METRIC_RSSI_BEACON;
	acx->type = WL1271_ACX_TRIG_TYPE_EDGE;
	if (enable)
		acx->enable = WL1271_ACX_TRIG_ENABLE;
	else
		acx->enable = WL1271_ACX_TRIG_DISABLE;

	acx->index = WL1271_ACX_TRIG_IDX_RSSI;
	acx->dir = WL1271_ACX_TRIG_DIR_BIDIR;
	acx->threshold = cpu_to_le16(thold);
	acx->hysteresis = hyst;

	ret = wl1271_cmd_configure(wl, ACX_RSSI_SNR_TRIGGER, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx rssi snr trigger setting failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}