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
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_ASIS ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int desc_to_gpio (struct gpio_desc*) ; 
 struct gpio_desc* gpiod_get_index (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (struct gpio_desc*) ; 

__attribute__((used)) static int surface3_button_lookup_gpio(struct device *dev, int acpi_index)
{
	struct gpio_desc *desc;
	int gpio;

	desc = gpiod_get_index(dev, NULL, acpi_index, GPIOD_ASIS);
	if (IS_ERR(desc))
		return PTR_ERR(desc);

	gpio = desc_to_gpio(desc);

	gpiod_put(desc);

	return gpio;
}