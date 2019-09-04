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
struct r8152 {int version; int /*<<< orphan*/  coalesce; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  RTL_VER_01 130 
#define  RTL_VER_02 129 
#define  RTL_VER_07 128 
 struct r8152* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtl8152_get_coalesce(struct net_device *netdev,
				struct ethtool_coalesce *coalesce)
{
	struct r8152 *tp = netdev_priv(netdev);

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		return -EOPNOTSUPP;
	default:
		break;
	}

	coalesce->rx_coalesce_usecs = tp->coalesce;

	return 0;
}