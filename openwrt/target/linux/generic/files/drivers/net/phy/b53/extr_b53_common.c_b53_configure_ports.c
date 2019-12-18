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
typedef  int u8 ;
struct TYPE_2__ {int cpu_port; } ;
struct b53_device {int enabled_ports; TYPE_1__ sw_dev; } ;

/* Variables and functions */
 int B53_CPU_PORT ; 
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int B53_GMII_PORT_OVERRIDE_CTRL (int) ; 
 int B53_PORT_OVERRIDE_CTRL ; 
 int BIT (int) ; 
 int EINVAL ; 
 int GMII_PO_EN ; 
 int GMII_PO_LINK ; 
 int GMII_PO_RX_FLOW ; 
 int GMII_PO_SPEED_2000M ; 
 int GMII_PO_TX_FLOW ; 
 int PORT_OVERRIDE_EN ; 
 int PORT_OVERRIDE_LINK ; 
 int PORT_OVERRIDE_RV_MII_25 ; 
 int PORT_OVERRIDE_RX_FLOW ; 
 int PORT_OVERRIDE_SPEED_2000M ; 
 int PORT_OVERRIDE_TX_FLOW ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ is5301x (struct b53_device*) ; 
 scalar_t__ is531x5 (struct b53_device*) ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int b53_configure_ports(struct b53_device *dev)
{
	u8 cpu_port = dev->sw_dev.cpu_port;

	/* configure MII port if necessary */
	if (is5325(dev)) {
		u8 mii_port_override;

		b53_read8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
			  &mii_port_override);
		/* reverse mii needs to be enabled */
		if (!(mii_port_override & PORT_OVERRIDE_RV_MII_25)) {
			b53_write8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				   mii_port_override | PORT_OVERRIDE_RV_MII_25);
			b53_read8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				  &mii_port_override);

			if (!(mii_port_override & PORT_OVERRIDE_RV_MII_25)) {
				pr_err("Failed to enable reverse MII mode\n");
				return -EINVAL;
			}
		}
	} else if (is531x5(dev) && cpu_port == B53_CPU_PORT) {
		u8 mii_port_override;

		b53_read8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
			  &mii_port_override);
		b53_write8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
			   mii_port_override | PORT_OVERRIDE_EN |
			   PORT_OVERRIDE_LINK);

		/* BCM47189 has another interface connected to the port 5 */
		if (dev->enabled_ports & BIT(5)) {
			u8 po_reg = B53_GMII_PORT_OVERRIDE_CTRL(5);
			u8 gmii_po;

			b53_read8(dev, B53_CTRL_PAGE, po_reg, &gmii_po);
			gmii_po |= GMII_PO_LINK |
				   GMII_PO_RX_FLOW |
				   GMII_PO_TX_FLOW |
				   GMII_PO_EN;
			b53_write8(dev, B53_CTRL_PAGE, po_reg, gmii_po);
		}
	} else if (is5301x(dev)) {
		if (cpu_port == 8) {
			u8 mii_port_override;

			b53_read8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				  &mii_port_override);
			mii_port_override |= PORT_OVERRIDE_LINK |
					     PORT_OVERRIDE_RX_FLOW |
					     PORT_OVERRIDE_TX_FLOW |
					     PORT_OVERRIDE_SPEED_2000M |
					     PORT_OVERRIDE_EN;
			b53_write8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				   mii_port_override);

			/* TODO: Ports 5 & 7 require some extra handling */
		} else {
			u8 po_reg = B53_GMII_PORT_OVERRIDE_CTRL(cpu_port);
			u8 gmii_po;

			b53_read8(dev, B53_CTRL_PAGE, po_reg, &gmii_po);
			gmii_po |= GMII_PO_LINK |
				   GMII_PO_RX_FLOW |
				   GMII_PO_TX_FLOW |
				   GMII_PO_EN |
				   GMII_PO_SPEED_2000M;
			b53_write8(dev, B53_CTRL_PAGE, po_reg, gmii_po);
		}
	}

	return 0;
}