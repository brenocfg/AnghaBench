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
struct cpcap_phy_ddata {int /*<<< orphan*/ * gpio; } ;
typedef  enum cpcap_gpio_mode { ____Placeholder_cpcap_gpio_mode } cpcap_gpio_mode ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpcap_usb_gpio_set_mode(struct cpcap_phy_ddata *ddata,
				   enum cpcap_gpio_mode mode)
{
	if (!ddata->gpio[0] || !ddata->gpio[1])
		return 0;

	gpiod_set_value(ddata->gpio[0], mode & 1);
	gpiod_set_value(ddata->gpio[1], mode >> 1);

	return 0;
}