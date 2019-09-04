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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int __nl80211_rx_control_port (struct net_device*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cfg80211_return_bool (int) ; 
 int /*<<< orphan*/  trace_cfg80211_rx_control_port (struct net_device*,struct sk_buff*,int) ; 

bool cfg80211_rx_control_port(struct net_device *dev,
			      struct sk_buff *skb, bool unencrypted)
{
	int ret;

	trace_cfg80211_rx_control_port(dev, skb, unencrypted);
	ret = __nl80211_rx_control_port(dev, skb, unencrypted, GFP_ATOMIC);
	trace_cfg80211_return_bool(ret == 0);
	return ret == 0;
}