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

__attribute__((used)) static void ich6_lpc_generic_decode(struct pci_dev *dev, unsigned reg,
				    const char *name, int dynsize)
{
	u32 val;
	u32 size, base;

	pci_read_config_dword(dev, reg, &val);

	/* Enabled? */
	if (!(val & 1))
		return;
	base = val & 0xfffc;
	if (dynsize) {
		/*
		 * This is not correct. It is 16, 32 or 64 bytes depending on
		 * register D31:F0:ADh bits 5:4.
		 *
		 * But this gets us at least _part_ of it.
		 */
		size = 16;
	} else {
		size = 128;
	}
	base &= ~(size-1);

	/*
	 * Just print it out for now. We should reserve it after more
	 * debugging.
	 */
	pci_info(dev, "%s PIO at %04x-%04x\n", name, base, base+size-1);
}