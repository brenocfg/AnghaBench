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
struct b43_phy {scalar_t__ type; int rev; int gmode; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_txpower_lo_control {int /*<<< orphan*/  bbatt_list; int /*<<< orphan*/  rfatt_list; } ;
struct b43_phy_g {int tx_control; int /*<<< orphan*/  rfatt; int /*<<< orphan*/  bbatt; struct b43_txpower_lo_control* lo_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_phy_initg (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_wireless_core_reset (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  default_baseband_attenuation (struct b43_wldev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_radio_attenuation (struct b43_wldev*,int /*<<< orphan*/ *) ; 
 int default_tx_control (struct b43_wldev*) ; 
 int /*<<< orphan*/  generate_bbatt_list (struct b43_wldev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_rfatt_list (struct b43_wldev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b43_gphy_op_prepare_hardware(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_txpower_lo_control *lo = gphy->lo_control;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	default_baseband_attenuation(dev, &gphy->bbatt);
	default_radio_attenuation(dev, &gphy->rfatt);
	gphy->tx_control = (default_tx_control(dev) << 4);
	generate_rfatt_list(dev, &lo->rfatt_list);
	generate_bbatt_list(dev, &lo->bbatt_list);

	/* Commit previous writes */
	b43_read32(dev, B43_MMIO_MACCTL);

	if (phy->rev == 1) {
		/* Workaround: Temporarly disable gmode through the early init
		 * phase, as the gmode stuff is not needed for phy rev 1 */
		phy->gmode = false;
		b43_wireless_core_reset(dev, 0);
		b43_phy_initg(dev);
		phy->gmode = true;
		b43_wireless_core_reset(dev, 1);
	}

	return 0;
}