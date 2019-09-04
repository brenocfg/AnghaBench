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
typedef  scalar_t__ u8 ;
struct wl12xx_vif {int /*<<< orphan*/  ssid; scalar_t__ ssid_len; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IEEE80211_MAX_SSID_LEN ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 scalar_t__* cfg80211_find_ie (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

__attribute__((used)) static int wl1271_ssid_set(struct wl12xx_vif *wlvif, struct sk_buff *skb,
			    int offset)
{
	u8 ssid_len;
	const u8 *ptr = cfg80211_find_ie(WLAN_EID_SSID, skb->data + offset,
					 skb->len - offset);

	if (!ptr) {
		wl1271_error("No SSID in IEs!");
		return -ENOENT;
	}

	ssid_len = ptr[1];
	if (ssid_len > IEEE80211_MAX_SSID_LEN) {
		wl1271_error("SSID is too long!");
		return -EINVAL;
	}

	wlvif->ssid_len = ssid_len;
	memcpy(wlvif->ssid, ptr+2, ssid_len);
	return 0;
}