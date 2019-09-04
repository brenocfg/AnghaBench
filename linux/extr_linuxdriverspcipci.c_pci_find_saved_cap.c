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
struct pci_cap_saved_state {int dummy; } ;

/* Variables and functions */
 struct pci_cap_saved_state* _pci_find_saved_cap (struct pci_dev*,char,int) ; 

struct pci_cap_saved_state *pci_find_saved_cap(struct pci_dev *dev, char cap)
{
	return _pci_find_saved_cap(dev, cap, false);
}