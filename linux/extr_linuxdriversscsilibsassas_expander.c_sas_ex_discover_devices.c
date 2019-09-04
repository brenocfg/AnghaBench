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
struct expander_device {int num_phys; struct ex_phy* ex_phy; } ;
struct ex_phy {scalar_t__ phy_state; int linkrate; } ;
struct domain_device {struct expander_device ex_dev; } ;

/* Variables and functions */
 scalar_t__ PHY_DEVICE_DISCOVERED ; 
 scalar_t__ PHY_NOT_PRESENT ; 
 scalar_t__ PHY_VACANT ; 
#define  SAS_PHY_DISABLED 130 
#define  SAS_PHY_RESET_PROBLEM 129 
#define  SAS_SATA_PORT_SELECTOR 128 
 int /*<<< orphan*/  sas_check_level_subtractive_boundary (struct domain_device*) ; 
 int sas_ex_discover_dev (struct domain_device*,int) ; 

__attribute__((used)) static int sas_ex_discover_devices(struct domain_device *dev, int single)
{
	struct expander_device *ex = &dev->ex_dev;
	int i = 0, end = ex->num_phys;
	int res = 0;

	if (0 <= single && single < end) {
		i = single;
		end = i+1;
	}

	for ( ; i < end; i++) {
		struct ex_phy *ex_phy = &ex->ex_phy[i];

		if (ex_phy->phy_state == PHY_VACANT ||
		    ex_phy->phy_state == PHY_NOT_PRESENT ||
		    ex_phy->phy_state == PHY_DEVICE_DISCOVERED)
			continue;

		switch (ex_phy->linkrate) {
		case SAS_PHY_DISABLED:
		case SAS_PHY_RESET_PROBLEM:
		case SAS_SATA_PORT_SELECTOR:
			continue;
		default:
			res = sas_ex_discover_dev(dev, i);
			if (res)
				break;
			continue;
		}
	}

	if (!res)
		sas_check_level_subtractive_boundary(dev);

	return res;
}