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
typedef  int u32 ;
struct smsc911x_platform_config {int phy_interface; int shift; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_type; int /*<<< orphan*/  irq_polarity; int /*<<< orphan*/  mac; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int PHY_INTERFACE_MODE_NA ; 
 int /*<<< orphan*/  SMSC911X_FORCE_EXTERNAL_PHY ; 
 int /*<<< orphan*/  SMSC911X_FORCE_INTERNAL_PHY ; 
 int /*<<< orphan*/  SMSC911X_IRQ_POLARITY_ACTIVE_HIGH ; 
 int /*<<< orphan*/  SMSC911X_IRQ_TYPE_PUSH_PULL ; 
 int /*<<< orphan*/  SMSC911X_SAVE_MAC_ADDRESS ; 
 int /*<<< orphan*/  SMSC911X_USE_16BIT ; 
 int /*<<< orphan*/  SMSC911X_USE_32BIT ; 
 int /*<<< orphan*/  device_get_mac_address (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_phy_mode (struct device*) ; 
 scalar_t__ device_property_present (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 

__attribute__((used)) static int smsc911x_probe_config(struct smsc911x_platform_config *config,
				 struct device *dev)
{
	int phy_interface;
	u32 width = 0;
	int err;

	phy_interface = device_get_phy_mode(dev);
	if (phy_interface < 0)
		phy_interface = PHY_INTERFACE_MODE_NA;
	config->phy_interface = phy_interface;

	device_get_mac_address(dev, config->mac, ETH_ALEN);

	err = device_property_read_u32(dev, "reg-io-width", &width);
	if (err == -ENXIO)
		return err;
	if (!err && width == 4)
		config->flags |= SMSC911X_USE_32BIT;
	else
		config->flags |= SMSC911X_USE_16BIT;

	device_property_read_u32(dev, "reg-shift", &config->shift);

	if (device_property_present(dev, "smsc,irq-active-high"))
		config->irq_polarity = SMSC911X_IRQ_POLARITY_ACTIVE_HIGH;

	if (device_property_present(dev, "smsc,irq-push-pull"))
		config->irq_type = SMSC911X_IRQ_TYPE_PUSH_PULL;

	if (device_property_present(dev, "smsc,force-internal-phy"))
		config->flags |= SMSC911X_FORCE_INTERNAL_PHY;

	if (device_property_present(dev, "smsc,force-external-phy"))
		config->flags |= SMSC911X_FORCE_EXTERNAL_PHY;

	if (device_property_present(dev, "smsc,save-mac-address"))
		config->flags |= SMSC911X_SAVE_MAC_ADDRESS;

	return 0;
}