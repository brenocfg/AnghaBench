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
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static bool s626_mc_test(struct comedi_device *dev,
			 unsigned int cmd, unsigned int reg)
{
	unsigned int val;

	val = readl(dev->mmio + reg);

	return (val & cmd) ? true : false;
}