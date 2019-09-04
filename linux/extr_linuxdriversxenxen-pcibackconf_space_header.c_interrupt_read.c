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
typedef  scalar_t__ u8 ;
struct pci_dev {scalar_t__ irq; } ;

/* Variables and functions */

__attribute__((used)) static int interrupt_read(struct pci_dev *dev, int offset, u8 * value,
			  void *data)
{
	*value = (u8) dev->irq;

	return 0;
}