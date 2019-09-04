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
struct b43_phy {scalar_t__ type; scalar_t__ rev; int /*<<< orphan*/  gmode; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_g {int aci_wlan_automatic; int aci_enable; int interfmode; int aci_hw_rssi; } ;
typedef  enum b43_interference_mitigation { ____Placeholder_b43_interference_mitigation } b43_interference_mitigation ;

/* Variables and functions */
#define  B43_INTERFMODE_AUTOWLAN 131 
#define  B43_INTERFMODE_MANUALWLAN 130 
#define  B43_INTERFMODE_NONE 129 
#define  B43_INTERFMODE_NONWLAN 128 
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  b43_radio_interference_mitigation_disable (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_interference_mitigation_enable (struct b43_wldev*,int) ; 

__attribute__((used)) static int b43_gphy_op_interf_mitigation(struct b43_wldev *dev,
					 enum b43_interference_mitigation mode)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	int currentmode;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);
	if ((phy->rev == 0) || (!phy->gmode))
		return -ENODEV;

	gphy->aci_wlan_automatic = false;
	switch (mode) {
	case B43_INTERFMODE_AUTOWLAN:
		gphy->aci_wlan_automatic = true;
		if (gphy->aci_enable)
			mode = B43_INTERFMODE_MANUALWLAN;
		else
			mode = B43_INTERFMODE_NONE;
		break;
	case B43_INTERFMODE_NONE:
	case B43_INTERFMODE_NONWLAN:
	case B43_INTERFMODE_MANUALWLAN:
		break;
	default:
		return -EINVAL;
	}

	currentmode = gphy->interfmode;
	if (currentmode == mode)
		return 0;
	if (currentmode != B43_INTERFMODE_NONE)
		b43_radio_interference_mitigation_disable(dev, currentmode);

	if (mode == B43_INTERFMODE_NONE) {
		gphy->aci_enable = false;
		gphy->aci_hw_rssi = false;
	} else
		b43_radio_interference_mitigation_enable(dev, mode);
	gphy->interfmode = mode;

	return 0;
}