#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {struct device* parent; struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int CTL1000_AS_MASTER ; 
 int CTL1000_ENABLE_MASTER ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_KSZ9031RN_CLK_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031RN_CONTROL_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031RN_RX_DATA_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031RN_TX_DATA_PAD_SKEW ; 
 int ksz9031_center_flp_timing (struct phy_device*) ; 
 int ksz9031_enable_edpd (struct phy_device*) ; 
 int /*<<< orphan*/  ksz9031_of_load_skew_values (struct phy_device*,struct device_node const*,int /*<<< orphan*/ ,int,char const**,int) ; 
 scalar_t__ of_property_read_bool (struct device_node const*,char*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*) ; 

__attribute__((used)) static int ksz9031_config_init(struct phy_device *phydev)
{
	const struct device *dev = &phydev->mdio.dev;
	const struct device_node *of_node = dev->of_node;
	static const char *clk_skews[2] = {"rxc-skew-ps", "txc-skew-ps"};
	static const char *rx_data_skews[4] = {
		"rxd0-skew-ps", "rxd1-skew-ps",
		"rxd2-skew-ps", "rxd3-skew-ps"
	};
	static const char *tx_data_skews[4] = {
		"txd0-skew-ps", "txd1-skew-ps",
		"txd2-skew-ps", "txd3-skew-ps"
	};
	static const char *control_skews[2] = {"txen-skew-ps", "rxdv-skew-ps"};
	const struct device *dev_walker;
	int result;

	result = ksz9031_enable_edpd(phydev);
	if (result < 0)
		return result;

	/* The Micrel driver has a deprecated option to place phy OF
	 * properties in the MAC node. Walk up the tree of devices to
	 * find a device with an OF node.
	 */
	dev_walker = &phydev->mdio.dev;
	do {
		of_node = dev_walker->of_node;
		dev_walker = dev_walker->parent;
	} while (!of_node && dev_walker);

	if (of_node) {
		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_CLK_PAD_SKEW, 5,
				clk_skews, 2);

		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_CONTROL_PAD_SKEW, 4,
				control_skews, 2);

		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_RX_DATA_PAD_SKEW, 4,
				rx_data_skews, 4);

		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_TX_DATA_PAD_SKEW, 4,
				tx_data_skews, 4);

		/* Silicon Errata Sheet (DS80000691D or DS80000692D):
		 * When the device links in the 1000BASE-T slave mode only,
		 * the optional 125MHz reference output clock (CLK125_NDO)
		 * has wide duty cycle variation.
		 *
		 * The optional CLK125_NDO clock does not meet the RGMII
		 * 45/55 percent (min/max) duty cycle requirement and therefore
		 * cannot be used directly by the MAC side for clocking
		 * applications that have setup/hold time requirements on
		 * rising and falling clock edges.
		 *
		 * Workaround:
		 * Force the phy to be the master to receive a stable clock
		 * which meets the duty cycle requirement.
		 */
		if (of_property_read_bool(of_node, "micrel,force-master")) {
			result = phy_read(phydev, MII_CTRL1000);
			if (result < 0)
				goto err_force_master;

			/* enable master mode, config & prefer master */
			result |= CTL1000_ENABLE_MASTER | CTL1000_AS_MASTER;
			result = phy_write(phydev, MII_CTRL1000, result);
			if (result < 0)
				goto err_force_master;
		}
	}

	return ksz9031_center_flp_timing(phydev);

err_force_master:
	phydev_err(phydev, "failed to force the phy to master mode\n");
	return result;
}