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
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_hides_smbus ; 
 int /*<<< orphan*/ * asus_rcba_base ; 
 int /*<<< orphan*/ * ioremap_nocache (int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 

__attribute__((used)) static void asus_hides_smbus_lpc_ich6_suspend(struct pci_dev *dev)
{
	u32 rcba;

	if (likely(!asus_hides_smbus))
		return;
	WARN_ON(asus_rcba_base);

	pci_read_config_dword(dev, 0xF0, &rcba);
	/* use bits 31:14, 16 kB aligned */
	asus_rcba_base = ioremap_nocache(rcba & 0xFFFFC000, 0x4000);
	if (asus_rcba_base == NULL)
		return;
}