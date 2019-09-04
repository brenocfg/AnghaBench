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
 int _pci_add_cap_save_buffer (struct pci_dev*,char,int,unsigned int) ; 

int pci_add_cap_save_buffer(struct pci_dev *dev, char cap, unsigned int size)
{
	return _pci_add_cap_save_buffer(dev, cap, false, size);
}