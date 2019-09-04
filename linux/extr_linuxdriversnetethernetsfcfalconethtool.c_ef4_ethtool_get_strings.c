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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ef4_nic {TYPE_1__* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int (* describe_stats ) (struct ef4_nic*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EF4_ETHTOOL_SW_STAT_COUNT ; 
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int ef4_describe_per_queue_stats (struct ef4_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ef4_ethtool_fill_self_tests (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* ef4_sw_stat_desc ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ef4_nic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ef4_ethtool_get_strings(struct net_device *net_dev,
				    u32 string_set, u8 *strings)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	int i;

	switch (string_set) {
	case ETH_SS_STATS:
		strings += (efx->type->describe_stats(efx, strings) *
			    ETH_GSTRING_LEN);
		for (i = 0; i < EF4_ETHTOOL_SW_STAT_COUNT; i++)
			strlcpy(strings + i * ETH_GSTRING_LEN,
				ef4_sw_stat_desc[i].name, ETH_GSTRING_LEN);
		strings += EF4_ETHTOOL_SW_STAT_COUNT * ETH_GSTRING_LEN;
		strings += (ef4_describe_per_queue_stats(efx, strings) *
			    ETH_GSTRING_LEN);
		break;
	case ETH_SS_TEST:
		ef4_ethtool_fill_self_tests(efx, NULL, strings, NULL);
		break;
	default:
		/* No other string sets */
		break;
	}
}