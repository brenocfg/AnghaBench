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
typedef  int /*<<< orphan*/  u32 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; int /*<<< orphan*/  basic_rate_set; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;
struct ieee80211_hdr_3addr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEMPL_NULL_DATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FTYPE_DATA ; 
 int IEEE80211_STYPE_NULLFUNC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_hdr_3addr*) ; 
 struct ieee80211_hdr_3addr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_template_set (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_hdr_3addr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_tx_min_rate_get (struct wl1271*,int /*<<< orphan*/ ) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static int wl1271_ap_init_null_template(struct wl1271 *wl,
					struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct ieee80211_hdr_3addr *nullfunc;
	int ret;
	u32 rate;

	nullfunc = kzalloc(sizeof(*nullfunc), GFP_KERNEL);
	if (!nullfunc) {
		ret = -ENOMEM;
		goto out;
	}

	nullfunc->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					      IEEE80211_STYPE_NULLFUNC |
					      IEEE80211_FCTL_FROMDS);

	/* nullfunc->addr1 is filled by FW */

	memcpy(nullfunc->addr2, vif->addr, ETH_ALEN);
	memcpy(nullfunc->addr3, vif->addr, ETH_ALEN);

	rate = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_NULL_DATA, nullfunc,
				      sizeof(*nullfunc), 0, rate);

out:
	kfree(nullfunc);
	return ret;
}