#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {size_t len; scalar_t__ cb; scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_if_managed {TYPE_5__* associated; } ;
struct TYPE_6__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; TYPE_1__ u; } ;
struct ieee80211_rx_status {int dummy; } ;
struct TYPE_8__ {scalar_t__ variable; } ;
struct TYPE_9__ {TYPE_3__ probe_resp; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  bssid; TYPE_4__ u; int /*<<< orphan*/  da; } ;
struct TYPE_10__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_reset_ap_probe (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_rx_bss_info (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,size_t,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static void ieee80211_rx_mgmt_probe_resp(struct ieee80211_sub_if_data *sdata,
					 struct sk_buff *skb)
{
	struct ieee80211_mgmt *mgmt = (void *)skb->data;
	struct ieee80211_if_managed *ifmgd;
	struct ieee80211_rx_status *rx_status = (void *) skb->cb;
	size_t baselen, len = skb->len;

	ifmgd = &sdata->u.mgd;

	sdata_assert_lock(sdata);

	if (!ether_addr_equal(mgmt->da, sdata->vif.addr))
		return; /* ignore ProbeResp to foreign address */

	baselen = (u8 *) mgmt->u.probe_resp.variable - (u8 *) mgmt;
	if (baselen > len)
		return;

	ieee80211_rx_bss_info(sdata, mgmt, len, rx_status);

	if (ifmgd->associated &&
	    ether_addr_equal(mgmt->bssid, ifmgd->associated->bssid))
		ieee80211_reset_ap_probe(sdata);
}