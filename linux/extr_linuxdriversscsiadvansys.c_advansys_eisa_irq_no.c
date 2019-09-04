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
struct eisa_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 unsigned short inw (scalar_t__) ; 

__attribute__((used)) static unsigned int advansys_eisa_irq_no(struct eisa_device *edev)
{
	unsigned short cfg_lsw = inw(edev->base_addr + 0xc86);
	unsigned int chip_irq = ((cfg_lsw >> 8) & 0x07) + 10;
	if ((chip_irq == 13) || (chip_irq > 15))
		return 0;
	return chip_irq;
}