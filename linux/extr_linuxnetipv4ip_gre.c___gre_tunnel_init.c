#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/  hw_features; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {int o_flags; TYPE_1__ iph; } ;
struct ip_tunnel {TYPE_3__ encap; TYPE_2__ parms; scalar_t__ encap_hlen; scalar_t__ tun_hlen; scalar_t__ hlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRE_FEATURES ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int /*<<< orphan*/  NETIF_F_GSO_SOFTWARE ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int TUNNEL_CSUM ; 
 scalar_t__ TUNNEL_ENCAP_NONE ; 
 int TUNNEL_SEQ ; 
 scalar_t__ gre_calc_hlen (int) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void __gre_tunnel_init(struct net_device *dev)
{
	struct ip_tunnel *tunnel;

	tunnel = netdev_priv(dev);
	tunnel->tun_hlen = gre_calc_hlen(tunnel->parms.o_flags);
	tunnel->parms.iph.protocol = IPPROTO_GRE;

	tunnel->hlen = tunnel->tun_hlen + tunnel->encap_hlen;

	dev->features		|= GRE_FEATURES;
	dev->hw_features	|= GRE_FEATURES;

	if (!(tunnel->parms.o_flags & TUNNEL_SEQ)) {
		/* TCP offload with GRE SEQ is not supported, nor
		 * can we support 2 levels of outer headers requiring
		 * an update.
		 */
		if (!(tunnel->parms.o_flags & TUNNEL_CSUM) ||
		    (tunnel->encap.type == TUNNEL_ENCAP_NONE)) {
			dev->features    |= NETIF_F_GSO_SOFTWARE;
			dev->hw_features |= NETIF_F_GSO_SOFTWARE;
		}

		/* Can use a lockless transmit, unless we generate
		 * output sequences
		 */
		dev->features |= NETIF_F_LLTX;
	}
}