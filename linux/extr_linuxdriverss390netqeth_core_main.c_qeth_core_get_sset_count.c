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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  qeth_ethtool_stats_keys ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 

int qeth_core_get_sset_count(struct net_device *dev, int stringset)
{
	switch (stringset) {
	case ETH_SS_STATS:
		return (sizeof(qeth_ethtool_stats_keys) / ETH_GSTRING_LEN);
	default:
		return -EINVAL;
	}
}