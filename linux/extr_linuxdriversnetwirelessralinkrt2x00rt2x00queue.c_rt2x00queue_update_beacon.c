#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct txentry_desc {int dummy; } ;
struct skb_frame_desc {int dummy; } ;
struct rt2x00_intf {TYPE_3__* beacon; } ;
struct rt2x00_dev {TYPE_2__* ops; int /*<<< orphan*/  hw; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  skb; } ;
struct TYPE_6__ {TYPE_1__* lib; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* write_beacon ) (TYPE_3__*,struct txentry_desc*) ;} ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 struct skb_frame_desc* get_skb_frame_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_beacon_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memset (struct skb_frame_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00queue_create_tx_descriptor (struct rt2x00_dev*,int /*<<< orphan*/ ,struct txentry_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00queue_free_skb (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct txentry_desc*) ; 
 scalar_t__ unlikely (int) ; 
 struct rt2x00_intf* vif_to_intf (struct ieee80211_vif*) ; 

int rt2x00queue_update_beacon(struct rt2x00_dev *rt2x00dev,
			      struct ieee80211_vif *vif)
{
	struct rt2x00_intf *intf = vif_to_intf(vif);
	struct skb_frame_desc *skbdesc;
	struct txentry_desc txdesc;

	if (unlikely(!intf->beacon))
		return -ENOBUFS;

	/*
	 * Clean up the beacon skb.
	 */
	rt2x00queue_free_skb(intf->beacon);

	intf->beacon->skb = ieee80211_beacon_get(rt2x00dev->hw, vif);
	if (!intf->beacon->skb)
		return -ENOMEM;

	/*
	 * Copy all TX descriptor information into txdesc,
	 * after that we are free to use the skb->cb array
	 * for our information.
	 */
	rt2x00queue_create_tx_descriptor(rt2x00dev, intf->beacon->skb, &txdesc, NULL);

	/*
	 * Fill in skb descriptor
	 */
	skbdesc = get_skb_frame_desc(intf->beacon->skb);
	memset(skbdesc, 0, sizeof(*skbdesc));

	/*
	 * Send beacon to hardware.
	 */
	rt2x00dev->ops->lib->write_beacon(intf->beacon, &txdesc);

	return 0;

}