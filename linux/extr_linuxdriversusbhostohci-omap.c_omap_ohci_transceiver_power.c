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

/* Variables and functions */
 int /*<<< orphan*/  GPIO1 ; 
 int /*<<< orphan*/  HIGH ; 
 int /*<<< orphan*/  INNOVATOR_FPGA_CAM_USB_CONTROL ; 
 int /*<<< orphan*/  LOW ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_omap1510 () ; 
 scalar_t__ machine_is_omap_innovator () ; 
 scalar_t__ machine_is_omap_osk () ; 
 int /*<<< orphan*/  tps65010_set_gpio_out_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_ohci_transceiver_power(int on)
{
	if (on) {
		if (machine_is_omap_innovator() && cpu_is_omap1510())
			__raw_writeb(__raw_readb(INNOVATOR_FPGA_CAM_USB_CONTROL)
				| ((1 << 5/*usb1*/) | (1 << 3/*usb2*/)),
			       INNOVATOR_FPGA_CAM_USB_CONTROL);
		else if (machine_is_omap_osk())
			tps65010_set_gpio_out_value(GPIO1, LOW);
	} else {
		if (machine_is_omap_innovator() && cpu_is_omap1510())
			__raw_writeb(__raw_readb(INNOVATOR_FPGA_CAM_USB_CONTROL)
				& ~((1 << 5/*usb1*/) | (1 << 3/*usb2*/)),
			       INNOVATOR_FPGA_CAM_USB_CONTROL);
		else if (machine_is_omap_osk())
			tps65010_set_gpio_out_value(GPIO1, HIGH);
	}

	return 0;
}