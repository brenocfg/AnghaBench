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
 scalar_t__ NI_65XX_FILTER_ENA (int) ; 
 scalar_t__ NI_65XX_FILTER_REG ; 
 unsigned int ni_65xx_num_ports (struct comedi_device*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ni_65xx_disable_input_filters(struct comedi_device *dev)
{
	unsigned int num_ports = ni_65xx_num_ports(dev);
	int i;

	/* disable input filtering on all ports */
	for (i = 0; i < num_ports; ++i)
		writeb(0x00, dev->mmio + NI_65XX_FILTER_ENA(i));

	/* set filter interval to 0 (32bit reg) */
	writel(0x00000000, dev->mmio + NI_65XX_FILTER_REG);
}