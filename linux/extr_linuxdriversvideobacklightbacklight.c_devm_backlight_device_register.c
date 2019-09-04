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
struct device {int dummy; } ;
struct backlight_properties {int dummy; } ;
struct backlight_ops {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct backlight_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (char const*,struct device*,void*,struct backlight_ops const*,struct backlight_properties const*) ; 
 int /*<<< orphan*/  devm_backlight_device_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct backlight_device**) ; 
 struct backlight_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct backlight_device**) ; 

struct backlight_device *devm_backlight_device_register(struct device *dev,
	const char *name, struct device *parent, void *devdata,
	const struct backlight_ops *ops,
	const struct backlight_properties *props)
{
	struct backlight_device **ptr, *backlight;

	ptr = devres_alloc(devm_backlight_device_release, sizeof(*ptr),
			GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	backlight = backlight_device_register(name, parent, devdata, ops,
						props);
	if (!IS_ERR(backlight)) {
		*ptr = backlight;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return backlight;
}