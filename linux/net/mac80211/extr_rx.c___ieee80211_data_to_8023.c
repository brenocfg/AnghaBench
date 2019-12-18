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
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {scalar_t__ sta; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_4addr; } ;
struct TYPE_8__ {TYPE_2__ vlan; TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {scalar_t__ control_port_protocol; TYPE_4__ vif; TYPE_3__ u; } ;
struct ieee80211_rx_data {struct ieee80211_sub_if_data* sdata; TYPE_5__* skb; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
struct ethhdr {scalar_t__ h_proto; } ;
struct TYPE_10__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_data_to_8023 (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ieee80211_has_a4 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__ieee80211_data_to_8023(struct ieee80211_rx_data *rx, bool *port_control)
{
	struct ieee80211_sub_if_data *sdata = rx->sdata;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)rx->skb->data;
	bool check_port_control = false;
	struct ethhdr *ehdr;
	int ret;

	*port_control = false;
	if (ieee80211_has_a4(hdr->frame_control) &&
	    sdata->vif.type == NL80211_IFTYPE_AP_VLAN && !sdata->u.vlan.sta)
		return -1;

	if (sdata->vif.type == NL80211_IFTYPE_STATION &&
	    !!sdata->u.mgd.use_4addr != !!ieee80211_has_a4(hdr->frame_control)) {

		if (!sdata->u.mgd.use_4addr)
			return -1;
		else if (!ether_addr_equal(hdr->addr1, sdata->vif.addr))
			check_port_control = true;
	}

	if (is_multicast_ether_addr(hdr->addr1) &&
	    sdata->vif.type == NL80211_IFTYPE_AP_VLAN && sdata->u.vlan.sta)
		return -1;

	ret = ieee80211_data_to_8023(rx->skb, sdata->vif.addr, sdata->vif.type);
	if (ret < 0)
		return ret;

	ehdr = (struct ethhdr *) rx->skb->data;
	if (ehdr->h_proto == rx->sdata->control_port_protocol)
		*port_control = true;
	else if (check_port_control)
		return -1;

	return 0;
}