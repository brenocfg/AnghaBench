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
typedef  scalar_t__ u8 ;
struct wl1271 {TYPE_1__* hw; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WLCORE_VENDOR_ATTR_PSK ; 
 int /*<<< orphan*/  WLCORE_VENDOR_ATTR_SSID ; 
 int /*<<< orphan*/  WLCORE_VENDOR_EVENT_SC_DECODE ; 
 int /*<<< orphan*/  cfg80211_vendor_event (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* cfg80211_vendor_event_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_dump_ascii (int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int wlcore_smart_config_decode_event(struct wl1271 *wl,
					    u8 ssid_len, u8 *ssid,
					    u8 pwd_len, u8 *pwd)
{
	struct sk_buff *skb;

	wl1271_debug(DEBUG_EVENT, "SMART_CONFIG_DECODE_EVENT_ID");
	wl1271_dump_ascii(DEBUG_EVENT, "SSID:", ssid, ssid_len);

	skb = cfg80211_vendor_event_alloc(wl->hw->wiphy, NULL,
					  ssid_len + pwd_len + 20,
					  WLCORE_VENDOR_EVENT_SC_DECODE,
					  GFP_KERNEL);

	if (nla_put(skb, WLCORE_VENDOR_ATTR_SSID, ssid_len, ssid) ||
	    nla_put(skb, WLCORE_VENDOR_ATTR_PSK, pwd_len, pwd)) {
		kfree_skb(skb);
		return -EMSGSIZE;
	}
	cfg80211_vendor_event(skb, GFP_KERNEL);
	return 0;
}