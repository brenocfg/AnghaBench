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
struct msm_pinctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ device_property_read_u16_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool msm_gpio_needs_valid_mask(struct msm_pinctrl *pctrl)
{
	return device_property_read_u16_array(pctrl->dev, "gpios", NULL, 0) > 0;
}