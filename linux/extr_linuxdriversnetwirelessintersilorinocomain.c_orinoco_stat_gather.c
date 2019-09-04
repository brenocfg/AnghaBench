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
struct orinoco_private {int dummy; } ;
struct net_device {int dummy; } ;
struct hermes_rx_descriptor {int /*<<< orphan*/  silence; int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 scalar_t__ SPY_NUMBER (struct orinoco_private*) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 int /*<<< orphan*/  orinoco_spy_gather (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void orinoco_stat_gather(struct net_device *dev,
				struct sk_buff *skb,
				struct hermes_rx_descriptor *desc)
{
	struct orinoco_private *priv = ndev_priv(dev);

	/* Using spy support with lots of Rx packets, like in an
	 * infrastructure (AP), will really slow down everything, because
	 * the MAC address must be compared to each entry of the spy list.
	 * If the user really asks for it (set some address in the
	 * spy list), we do it, but he will pay the price.
	 * Note that to get here, you need both WIRELESS_SPY
	 * compiled in AND some addresses in the list !!!
	 */
	/* Note : gcc will optimise the whole section away if
	 * WIRELESS_SPY is not defined... - Jean II */
	if (SPY_NUMBER(priv)) {
		orinoco_spy_gather(dev, skb_mac_header(skb) + ETH_ALEN,
				   desc->signal, desc->silence);
	}
}