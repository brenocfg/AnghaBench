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
struct v3_pci {int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int INTEGRATOR_SC_PCI_ENABLE ; 
 unsigned int INTEGRATOR_SC_PCI_INTCLR ; 
 int /*<<< orphan*/  INTEGRATOR_SC_PCI_OFFSET ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ V3_LB_IO_BASE ; 
 scalar_t__ V3_MAIL_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_compatible (char*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int v3_integrator_init(struct v3_pci *v3)
{
	unsigned int val;

	v3->map =
		syscon_regmap_lookup_by_compatible("arm,integrator-ap-syscon");
	if (IS_ERR(v3->map)) {
		dev_err(v3->dev, "no syscon\n");
		return -ENODEV;
	}

	regmap_read(v3->map, INTEGRATOR_SC_PCI_OFFSET, &val);
	/* Take the PCI bridge out of reset, clear IRQs */
	regmap_write(v3->map, INTEGRATOR_SC_PCI_OFFSET,
		     INTEGRATOR_SC_PCI_ENABLE |
		     INTEGRATOR_SC_PCI_INTCLR);

	if (!(val & INTEGRATOR_SC_PCI_ENABLE)) {
		/* If we were in reset we need to sleep a bit */
		msleep(230);

		/* Set the physical base for the controller itself */
		writel(0x6200, v3->base + V3_LB_IO_BASE);

		/* Wait for the mailbox to settle after reset */
		do {
			writeb(0xaa, v3->base + V3_MAIL_DATA);
			writeb(0x55, v3->base + V3_MAIL_DATA + 4);
		} while (readb(v3->base + V3_MAIL_DATA) != 0xaa &&
			 readb(v3->base + V3_MAIL_DATA) != 0x55);
	}

	dev_info(v3->dev, "initialized PCI V3 Integrator/AP integration\n");

	return 0;
}