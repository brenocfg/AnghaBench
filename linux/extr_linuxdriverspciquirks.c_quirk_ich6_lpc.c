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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ich6_lpc_acpi_gpio (struct pci_dev*) ; 
 int /*<<< orphan*/  ich6_lpc_generic_decode (struct pci_dev*,int,char*,int) ; 

__attribute__((used)) static void quirk_ich6_lpc(struct pci_dev *dev)
{
	/* Shared ACPI/GPIO decode with all ICH6+ */
	ich6_lpc_acpi_gpio(dev);

	/* ICH6-specific generic IO decode */
	ich6_lpc_generic_decode(dev, 0x84, "LPC Generic IO decode 1", 0);
	ich6_lpc_generic_decode(dev, 0x88, "LPC Generic IO decode 2", 1);
}