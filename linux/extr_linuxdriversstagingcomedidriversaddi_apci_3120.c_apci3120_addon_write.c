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
struct comedi_device {struct apci3120_private* private; } ;
struct apci3120_private {scalar_t__ addon; } ;

/* Variables and functions */
 scalar_t__ APCI3120_ADDON_ADDR_REG ; 
 scalar_t__ APCI3120_ADDON_DATA_REG ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static void apci3120_addon_write(struct comedi_device *dev,
				 unsigned int val, unsigned int reg)
{
	struct apci3120_private *devpriv = dev->private;

	/* 16-bit interface for AMCC add-on registers */

	outw(reg, devpriv->addon + APCI3120_ADDON_ADDR_REG);
	outw(val & 0xffff, devpriv->addon + APCI3120_ADDON_DATA_REG);

	outw(reg + 2, devpriv->addon + APCI3120_ADDON_ADDR_REG);
	outw((val >> 16) & 0xffff, devpriv->addon + APCI3120_ADDON_DATA_REG);
}