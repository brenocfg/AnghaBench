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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ethtool_tunable {int id; int len; int /*<<< orphan*/  type_id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_PFC_PREVENTION_TOUT 130 
#define  ETHTOOL_RX_COPYBREAK 129 
 int /*<<< orphan*/  ETHTOOL_TUNABLE_U16 ; 
 int /*<<< orphan*/  ETHTOOL_TUNABLE_U32 ; 
#define  ETHTOOL_TX_COPYBREAK 128 

__attribute__((used)) static int ethtool_tunable_valid(const struct ethtool_tunable *tuna)
{
	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
	case ETHTOOL_TX_COPYBREAK:
		if (tuna->len != sizeof(u32) ||
		    tuna->type_id != ETHTOOL_TUNABLE_U32)
			return -EINVAL;
		break;
	case ETHTOOL_PFC_PREVENTION_TOUT:
		if (tuna->len != sizeof(u16) ||
		    tuna->type_id != ETHTOOL_TUNABLE_U16)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}