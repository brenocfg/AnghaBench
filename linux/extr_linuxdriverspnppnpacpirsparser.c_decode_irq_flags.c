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
typedef  int /*<<< orphan*/  u8 ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ACTIVE_HIGH ; 
 int /*<<< orphan*/  ACPI_ACTIVE_LOW ; 
 int /*<<< orphan*/  ACPI_EDGE_SENSITIVE ; 
 int /*<<< orphan*/  ACPI_EXCLUSIVE ; 
 int /*<<< orphan*/  ACPI_LEVEL_SENSITIVE ; 
 int /*<<< orphan*/  ACPI_SHARED ; 
#define  IORESOURCE_IRQ_HIGHEDGE 131 
#define  IORESOURCE_IRQ_HIGHLEVEL 130 
#define  IORESOURCE_IRQ_LOWEDGE 129 
#define  IORESOURCE_IRQ_LOWLEVEL 128 
 int IORESOURCE_IRQ_SHAREABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void decode_irq_flags(struct pnp_dev *dev, int flags, u8 *triggering,
			     u8 *polarity, u8 *shareable)
{
	switch (flags & (IORESOURCE_IRQ_LOWLEVEL | IORESOURCE_IRQ_HIGHLEVEL |
			 IORESOURCE_IRQ_LOWEDGE  | IORESOURCE_IRQ_HIGHEDGE)) {
	case IORESOURCE_IRQ_LOWLEVEL:
		*triggering = ACPI_LEVEL_SENSITIVE;
		*polarity = ACPI_ACTIVE_LOW;
		break;
	case IORESOURCE_IRQ_HIGHLEVEL:
		*triggering = ACPI_LEVEL_SENSITIVE;
		*polarity = ACPI_ACTIVE_HIGH;
		break;
	case IORESOURCE_IRQ_LOWEDGE:
		*triggering = ACPI_EDGE_SENSITIVE;
		*polarity = ACPI_ACTIVE_LOW;
		break;
	case IORESOURCE_IRQ_HIGHEDGE:
		*triggering = ACPI_EDGE_SENSITIVE;
		*polarity = ACPI_ACTIVE_HIGH;
		break;
	default:
		dev_err(&dev->dev, "can't encode invalid IRQ mode %#x\n",
			flags);
		*triggering = ACPI_EDGE_SENSITIVE;
		*polarity = ACPI_ACTIVE_HIGH;
		break;
	}

	if (flags & IORESOURCE_IRQ_SHAREABLE)
		*shareable = ACPI_SHARED;
	else
		*shareable = ACPI_EXCLUSIVE;
}