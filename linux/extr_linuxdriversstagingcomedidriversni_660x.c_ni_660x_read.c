#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ mmio; } ;
struct TYPE_2__ {unsigned int offset; int size; } ;

/* Variables and functions */
 unsigned int NI660X_CHIP_OFFSET ; 
 TYPE_1__* ni_660x_reg_data ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int readw (scalar_t__) ; 

__attribute__((used)) static unsigned int ni_660x_read(struct comedi_device *dev,
				 unsigned int chip, unsigned int reg)
{
	unsigned int addr = (chip * NI660X_CHIP_OFFSET) +
			    ni_660x_reg_data[reg].offset;

	if (ni_660x_reg_data[reg].size == 2)
		return readw(dev->mmio + addr);
	return readl(dev->mmio + addr);
}