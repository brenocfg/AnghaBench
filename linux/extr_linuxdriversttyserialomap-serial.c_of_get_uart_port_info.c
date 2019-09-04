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
struct omap_uart_port_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  uartclk; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 struct omap_uart_port_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct omap_uart_port_info *of_get_uart_port_info(struct device *dev)
{
	struct omap_uart_port_info *omap_up_info;

	omap_up_info = devm_kzalloc(dev, sizeof(*omap_up_info), GFP_KERNEL);
	if (!omap_up_info)
		return NULL; /* out of memory */

	of_property_read_u32(dev->of_node, "clock-frequency",
					 &omap_up_info->uartclk);

	omap_up_info->flags = UPF_BOOT_AUTOCONF;

	return omap_up_info;
}