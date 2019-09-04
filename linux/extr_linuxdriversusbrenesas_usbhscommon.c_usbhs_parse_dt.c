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
typedef  int /*<<< orphan*/  u32 ;
struct renesas_usbhs_driver_param {uintptr_t type; int enable_gpio; int has_usb_dmac; void* pipe_size; void* pipe_configs; int /*<<< orphan*/  buswait_bwait; } ;
struct renesas_usbhs_platform_info {struct renesas_usbhs_driver_param driver_param; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 uintptr_t USBHS_TYPE_RCAR_GEN2 ; 
 uintptr_t USBHS_TYPE_RCAR_GEN3 ; 
 uintptr_t USBHS_TYPE_RCAR_GEN3_WITH_PLL ; 
 uintptr_t USBHS_TYPE_RZA1 ; 
 struct renesas_usbhs_platform_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int of_get_named_gpio_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* usbhsc_new_pipe ; 

__attribute__((used)) static struct renesas_usbhs_platform_info *usbhs_parse_dt(struct device *dev)
{
	struct renesas_usbhs_platform_info *info;
	struct renesas_usbhs_driver_param *dparam;
	u32 tmp;
	int gpio;

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return NULL;

	dparam = &info->driver_param;
	dparam->type = (uintptr_t)of_device_get_match_data(dev);
	if (!of_property_read_u32(dev->of_node, "renesas,buswait", &tmp))
		dparam->buswait_bwait = tmp;
	gpio = of_get_named_gpio_flags(dev->of_node, "renesas,enable-gpio", 0,
				       NULL);
	if (gpio > 0)
		dparam->enable_gpio = gpio;

	if (dparam->type == USBHS_TYPE_RCAR_GEN2 ||
	    dparam->type == USBHS_TYPE_RCAR_GEN3 ||
	    dparam->type == USBHS_TYPE_RCAR_GEN3_WITH_PLL) {
		dparam->has_usb_dmac = 1;
		dparam->pipe_configs = usbhsc_new_pipe;
		dparam->pipe_size = ARRAY_SIZE(usbhsc_new_pipe);
	}

	if (dparam->type == USBHS_TYPE_RZA1) {
		dparam->pipe_configs = usbhsc_new_pipe;
		dparam->pipe_size = ARRAY_SIZE(usbhsc_new_pipe);
	}

	return info;
}