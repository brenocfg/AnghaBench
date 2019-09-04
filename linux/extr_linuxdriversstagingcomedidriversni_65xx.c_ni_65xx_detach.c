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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ NI_65XX_CTRL_REG ; 
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void ni_65xx_detach(struct comedi_device *dev)
{
	if (dev->mmio)
		writeb(0x00, dev->mmio + NI_65XX_CTRL_REG);
	comedi_pci_detach(dev);
}