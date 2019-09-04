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
struct ethtool_tunable {int id; int len; int /*<<< orphan*/  type_id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_PHY_DOWNSHIFT 128 
 int /*<<< orphan*/  ETHTOOL_TUNABLE_U8 ; 

__attribute__((used)) static int ethtool_phy_tunable_valid(const struct ethtool_tunable *tuna)
{
	switch (tuna->id) {
	case ETHTOOL_PHY_DOWNSHIFT:
		if (tuna->len != sizeof(u8) ||
		    tuna->type_id != ETHTOOL_TUNABLE_U8)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}