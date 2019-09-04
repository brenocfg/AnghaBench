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
 int /*<<< orphan*/  asus_hides_smbus ; 
 int /*<<< orphan*/ * asus_rcba_base ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 

__attribute__((used)) static void asus_hides_smbus_lpc_ich6_resume(struct pci_dev *dev)
{
	if (likely(!asus_hides_smbus || !asus_rcba_base))
		return;

	iounmap(asus_rcba_base);
	asus_rcba_base = NULL;
	pci_info(dev, "Enabled ICH6/i801 SMBus device\n");
}