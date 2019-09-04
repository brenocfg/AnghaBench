#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/  hw_features; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {int o_flags; } ;
struct ip6_tnl {TYPE_1__ encap; TYPE_2__ parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRE6_FEATURES ; 
 int /*<<< orphan*/  NETIF_F_GSO_SOFTWARE ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int TUNNEL_CSUM ; 
 scalar_t__ TUNNEL_ENCAP_NONE ; 
 int TUNNEL_SEQ ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ip6gre_tnl_init_features(struct net_device *dev)
{
	struct ip6_tnl *nt = netdev_priv(dev);

	dev->features		|= GRE6_FEATURES;
	dev->hw_features	|= GRE6_FEATURES;

	if (!(nt->parms.o_flags & TUNNEL_SEQ)) {
		/* TCP offload with GRE SEQ is not supported, nor
		 * can we support 2 levels of outer headers requiring
		 * an update.
		 */
		if (!(nt->parms.o_flags & TUNNEL_CSUM) ||
		    nt->encap.type == TUNNEL_ENCAP_NONE) {
			dev->features    |= NETIF_F_GSO_SOFTWARE;
			dev->hw_features |= NETIF_F_GSO_SOFTWARE;
		}

		/* Can use a lockless transmit, unless we generate
		 * output sequences
		 */
		dev->features |= NETIF_F_LLTX;
	}
}