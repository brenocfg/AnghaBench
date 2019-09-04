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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,char const*,int,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned int,int*) ; 

__attribute__((used)) static void ich7_lpc_generic_decode(struct pci_dev *dev, unsigned reg,
				    const char *name)
{
	u32 val;
	u32 mask, base;

	pci_read_config_dword(dev, reg, &val);

	/* Enabled? */
	if (!(val & 1))
		return;

	/* IO base in bits 15:2, mask in bits 23:18, both are dword-based */
	base = val & 0xfffc;
	mask = (val >> 16) & 0xfc;
	mask |= 3;

	/*
	 * Just print it out for now. We should reserve it after more
	 * debugging.
	 */
	pci_info(dev, "%s PIO at %04x (mask %04x)\n", name, base, mask);
}