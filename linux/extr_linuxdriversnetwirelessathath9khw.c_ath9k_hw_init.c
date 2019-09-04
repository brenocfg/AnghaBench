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
struct TYPE_4__ {int devid; } ;
struct ath_hw {TYPE_2__ hw_version; } ;
struct ath_common {TYPE_1__* bus_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  ath_bus_type; } ;

/* Variables and functions */
#define  AR2427_DEVID_PCIE 148 
#define  AR5416_AR9100_DEVID 147 
#define  AR5416_DEVID_PCI 146 
#define  AR5416_DEVID_PCIE 145 
#define  AR9160_DEVID_PCI 144 
#define  AR9280_DEVID_PCI 143 
#define  AR9280_DEVID_PCIE 142 
#define  AR9285_DEVID_PCIE 141 
#define  AR9287_DEVID_PCI 140 
#define  AR9287_DEVID_PCIE 139 
#define  AR9300_DEVID_AR9330 138 
#define  AR9300_DEVID_AR9340 137 
#define  AR9300_DEVID_AR9462 136 
#define  AR9300_DEVID_AR9485_PCIE 135 
#define  AR9300_DEVID_AR953X 134 
#define  AR9300_DEVID_AR9565 133 
#define  AR9300_DEVID_AR9580 132 
#define  AR9300_DEVID_PCIE 131 
#define  AR9300_DEVID_QCA955X 130 
#define  AR9300_DEVID_QCA956X 129 
#define  AR9485_DEVID_AR1111 128 
 int /*<<< orphan*/  ATH_USB ; 
 int EOPNOTSUPP ; 
 int __ath9k_hw_init (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dynack_init (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int) ; 

int ath9k_hw_init(struct ath_hw *ah)
{
	int ret;
	struct ath_common *common = ath9k_hw_common(ah);

	/* These are all the AR5008/AR9001/AR9002/AR9003 hardware family of chipsets */
	switch (ah->hw_version.devid) {
	case AR5416_DEVID_PCI:
	case AR5416_DEVID_PCIE:
	case AR5416_AR9100_DEVID:
	case AR9160_DEVID_PCI:
	case AR9280_DEVID_PCI:
	case AR9280_DEVID_PCIE:
	case AR9285_DEVID_PCIE:
	case AR9287_DEVID_PCI:
	case AR9287_DEVID_PCIE:
	case AR2427_DEVID_PCIE:
	case AR9300_DEVID_PCIE:
	case AR9300_DEVID_AR9485_PCIE:
	case AR9300_DEVID_AR9330:
	case AR9300_DEVID_AR9340:
	case AR9300_DEVID_QCA955X:
	case AR9300_DEVID_AR9580:
	case AR9300_DEVID_AR9462:
	case AR9485_DEVID_AR1111:
	case AR9300_DEVID_AR9565:
	case AR9300_DEVID_AR953X:
	case AR9300_DEVID_QCA956X:
		break;
	default:
		if (common->bus_ops->ath_bus_type == ATH_USB)
			break;
		ath_err(common, "Hardware device ID 0x%04x not supported\n",
			ah->hw_version.devid);
		return -EOPNOTSUPP;
	}

	ret = __ath9k_hw_init(ah);
	if (ret) {
		ath_err(common,
			"Unable to initialize hardware; initialization status: %d\n",
			ret);
		return ret;
	}

	ath_dynack_init(ah);

	return 0;
}