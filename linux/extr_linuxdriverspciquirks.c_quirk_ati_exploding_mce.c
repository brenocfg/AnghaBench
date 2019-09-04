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
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  request_region (int,int,char*) ; 

__attribute__((used)) static void quirk_ati_exploding_mce(struct pci_dev *dev)
{
	pci_info(dev, "ATI Northbridge, reserving I/O ports 0x3b0 to 0x3bb\n");
	/* Mae rhaid i ni beidio ag edrych ar y lleoliadiau I/O hyn */
	request_region(0x3b0, 0x0C, "RadeonIGP");
	request_region(0x3d3, 0x01, "RadeonIGP");
}