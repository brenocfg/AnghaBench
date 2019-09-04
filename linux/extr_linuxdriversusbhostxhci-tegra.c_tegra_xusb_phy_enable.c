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
struct tegra_xusb {unsigned int num_phys; int /*<<< orphan*/ * phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_xusb_phy_enable(struct tegra_xusb *tegra)
{
	unsigned int i;
	int err;

	for (i = 0; i < tegra->num_phys; i++) {
		err = phy_init(tegra->phys[i]);
		if (err)
			goto disable_phy;

		err = phy_power_on(tegra->phys[i]);
		if (err) {
			phy_exit(tegra->phys[i]);
			goto disable_phy;
		}
	}

	return 0;

disable_phy:
	while (i--) {
		phy_power_off(tegra->phys[i]);
		phy_exit(tegra->phys[i]);
	}

	return err;
}