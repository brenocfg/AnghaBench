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
struct TYPE_2__ {int /*<<< orphan*/  unack_srdy_int_nb; } ;
struct ifx_spi_device {TYPE_1__ gpio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ifx_spi_handle_srdy (struct ifx_spi_device*) ; 

__attribute__((used)) static irqreturn_t ifx_spi_srdy_interrupt(int irq, void *dev)
{
	struct ifx_spi_device *ifx_dev = dev;
	ifx_dev->gpio.unack_srdy_int_nb++;
	ifx_spi_handle_srdy(ifx_dev);
	return IRQ_HANDLED;
}