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
typedef  int /*<<< orphan*/  u32 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; int /*<<< orphan*/  basic_rate_set; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_ctl; } ;
struct wl12xx_disconn_template {TYPE_1__ header; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEMPL_DEAUTH_AP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct wl12xx_disconn_template*) ; 
 struct wl12xx_disconn_template* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_template_set (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl12xx_disconn_template*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_tx_min_rate_get (struct wl1271*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1271_ap_init_deauth_template(struct wl1271 *wl,
					  struct wl12xx_vif *wlvif)
{
	struct wl12xx_disconn_template *tmpl;
	int ret;
	u32 rate;

	tmpl = kzalloc(sizeof(*tmpl), GFP_KERNEL);
	if (!tmpl) {
		ret = -ENOMEM;
		goto out;
	}

	tmpl->header.frame_ctl = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					     IEEE80211_STYPE_DEAUTH);

	rate = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_DEAUTH_AP,
				      tmpl, sizeof(*tmpl), 0, rate);

out:
	kfree(tmpl);
	return ret;
}