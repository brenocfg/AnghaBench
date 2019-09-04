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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int DPAA2_ETH_NUM_EXTRA_STATS ; 
 int DPAA2_ETH_NUM_STATS ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int /*<<< orphan*/ * dpaa2_ethtool_extras ; 
 int /*<<< orphan*/ * dpaa2_ethtool_stats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpaa2_eth_get_strings(struct net_device *netdev, u32 stringset,
				  u8 *data)
{
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < DPAA2_ETH_NUM_STATS; i++) {
			strlcpy(p, dpaa2_ethtool_stats[i], ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < DPAA2_ETH_NUM_EXTRA_STATS; i++) {
			strlcpy(p, dpaa2_ethtool_extras[i], ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		break;
	}
}