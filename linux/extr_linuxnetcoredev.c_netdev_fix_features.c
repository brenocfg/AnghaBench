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
struct net_device {int gso_partial_features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_ALL_TSO ; 
 int NETIF_F_GRO_HW ; 
 int NETIF_F_GSO ; 
 int NETIF_F_GSO_PARTIAL ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXFCS ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_F_TSO_ECN ; 
 int NETIF_F_TSO_MANGLEID ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 

__attribute__((used)) static netdev_features_t netdev_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	/* Fix illegal checksum combinations */
	if ((features & NETIF_F_HW_CSUM) &&
	    (features & (NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM))) {
		netdev_warn(dev, "mixed HW and IP checksum settings.\n");
		features &= ~(NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM);
	}

	/* TSO requires that SG is present as well. */
	if ((features & NETIF_F_ALL_TSO) && !(features & NETIF_F_SG)) {
		netdev_dbg(dev, "Dropping TSO features since no SG feature.\n");
		features &= ~NETIF_F_ALL_TSO;
	}

	if ((features & NETIF_F_TSO) && !(features & NETIF_F_HW_CSUM) &&
					!(features & NETIF_F_IP_CSUM)) {
		netdev_dbg(dev, "Dropping TSO features since no CSUM feature.\n");
		features &= ~NETIF_F_TSO;
		features &= ~NETIF_F_TSO_ECN;
	}

	if ((features & NETIF_F_TSO6) && !(features & NETIF_F_HW_CSUM) &&
					 !(features & NETIF_F_IPV6_CSUM)) {
		netdev_dbg(dev, "Dropping TSO6 features since no CSUM feature.\n");
		features &= ~NETIF_F_TSO6;
	}

	/* TSO with IPv4 ID mangling requires IPv4 TSO be enabled */
	if ((features & NETIF_F_TSO_MANGLEID) && !(features & NETIF_F_TSO))
		features &= ~NETIF_F_TSO_MANGLEID;

	/* TSO ECN requires that TSO is present as well. */
	if ((features & NETIF_F_ALL_TSO) == NETIF_F_TSO_ECN)
		features &= ~NETIF_F_TSO_ECN;

	/* Software GSO depends on SG. */
	if ((features & NETIF_F_GSO) && !(features & NETIF_F_SG)) {
		netdev_dbg(dev, "Dropping NETIF_F_GSO since no SG feature.\n");
		features &= ~NETIF_F_GSO;
	}

	/* GSO partial features require GSO partial be set */
	if ((features & dev->gso_partial_features) &&
	    !(features & NETIF_F_GSO_PARTIAL)) {
		netdev_dbg(dev,
			   "Dropping partially supported GSO features since no GSO partial.\n");
		features &= ~dev->gso_partial_features;
	}

	if (!(features & NETIF_F_RXCSUM)) {
		/* NETIF_F_GRO_HW implies doing RXCSUM since every packet
		 * successfully merged by hardware must also have the
		 * checksum verified by hardware.  If the user does not
		 * want to enable RXCSUM, logically, we should disable GRO_HW.
		 */
		if (features & NETIF_F_GRO_HW) {
			netdev_dbg(dev, "Dropping NETIF_F_GRO_HW since no RXCSUM feature.\n");
			features &= ~NETIF_F_GRO_HW;
		}
	}

	/* LRO/HW-GRO features cannot be combined with RX-FCS */
	if (features & NETIF_F_RXFCS) {
		if (features & NETIF_F_LRO) {
			netdev_dbg(dev, "Dropping LRO feature since RX-FCS is requested.\n");
			features &= ~NETIF_F_LRO;
		}

		if (features & NETIF_F_GRO_HW) {
			netdev_dbg(dev, "Dropping HW-GRO feature since RX-FCS is requested.\n");
			features &= ~NETIF_F_GRO_HW;
		}
	}

	return features;
}