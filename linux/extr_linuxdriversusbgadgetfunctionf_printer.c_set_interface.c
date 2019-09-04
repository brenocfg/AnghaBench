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
struct printer_dev {unsigned int interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO (struct printer_dev*,char*,unsigned int) ; 
 int /*<<< orphan*/  printer_reset_interface (struct printer_dev*) ; 
 int set_printer_interface (struct printer_dev*) ; 

__attribute__((used)) static int set_interface(struct printer_dev *dev, unsigned number)
{
	int			result = 0;

	/* Free the current interface */
	printer_reset_interface(dev);

	result = set_printer_interface(dev);
	if (result)
		printer_reset_interface(dev);
	else
		dev->interface = number;

	if (!result)
		INFO(dev, "Using interface %x\n", number);

	return result;
}