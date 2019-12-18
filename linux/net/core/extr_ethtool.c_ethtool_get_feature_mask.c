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
typedef  int u32 ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  ETHTOOL_GGRO 139 
#define  ETHTOOL_GGSO 138 
#define  ETHTOOL_GRXCSUM 137 
#define  ETHTOOL_GSG 136 
#define  ETHTOOL_GTSO 135 
#define  ETHTOOL_GTXCSUM 134 
#define  ETHTOOL_SGRO 133 
#define  ETHTOOL_SGSO 132 
#define  ETHTOOL_SRXCSUM 131 
#define  ETHTOOL_SSG 130 
#define  ETHTOOL_STSO 129 
#define  ETHTOOL_STXCSUM 128 
 int NETIF_F_ALL_TSO ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_GRO ; 
 int NETIF_F_GSO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SCTP_CRC ; 
 int NETIF_F_SG ; 

__attribute__((used)) static netdev_features_t ethtool_get_feature_mask(u32 eth_cmd)
{
	/* feature masks of legacy discrete ethtool ops */

	switch (eth_cmd) {
	case ETHTOOL_GTXCSUM:
	case ETHTOOL_STXCSUM:
		return NETIF_F_CSUM_MASK | NETIF_F_SCTP_CRC;
	case ETHTOOL_GRXCSUM:
	case ETHTOOL_SRXCSUM:
		return NETIF_F_RXCSUM;
	case ETHTOOL_GSG:
	case ETHTOOL_SSG:
		return NETIF_F_SG;
	case ETHTOOL_GTSO:
	case ETHTOOL_STSO:
		return NETIF_F_ALL_TSO;
	case ETHTOOL_GGSO:
	case ETHTOOL_SGSO:
		return NETIF_F_GSO;
	case ETHTOOL_GGRO:
	case ETHTOOL_SGRO:
		return NETIF_F_GRO;
	default:
		BUG();
	}
}