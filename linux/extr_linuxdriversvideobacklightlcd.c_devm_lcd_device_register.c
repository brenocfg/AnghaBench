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
struct lcd_ops {int dummy; } ;
struct lcd_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct lcd_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  devm_lcd_device_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct lcd_device**) ; 
 struct lcd_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct lcd_device**) ; 
 struct lcd_device* lcd_device_register (char const*,struct device*,void*,struct lcd_ops*) ; 

struct lcd_device *devm_lcd_device_register(struct device *dev,
		const char *name, struct device *parent,
		void *devdata, struct lcd_ops *ops)
{
	struct lcd_device **ptr, *lcd;

	ptr = devres_alloc(devm_lcd_device_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	lcd = lcd_device_register(name, parent, devdata, ops);
	if (!IS_ERR(lcd)) {
		*ptr = lcd;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return lcd;
}