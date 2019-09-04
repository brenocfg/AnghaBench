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
struct cas {int /*<<< orphan*/  min_frame_size; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int N_TX_RINGS_MASK ; 
 scalar_t__ cas_xmit_tx_ringN (struct cas*,int,struct sk_buff*) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_padto (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t cas_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct cas *cp = netdev_priv(dev);

	/* this is only used as a load-balancing hint, so it doesn't
	 * need to be SMP safe
	 */
	static int ring;

	if (skb_padto(skb, cp->min_frame_size))
		return NETDEV_TX_OK;

	/* XXX: we need some higher-level QoS hooks to steer packets to
	 *      individual queues.
	 */
	if (cas_xmit_tx_ringN(cp, ring++ & N_TX_RINGS_MASK, skb))
		return NETDEV_TX_BUSY;
	return NETDEV_TX_OK;
}