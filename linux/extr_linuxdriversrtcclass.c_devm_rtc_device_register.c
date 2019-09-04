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
struct rtc_device {int dummy; } ;
struct rtc_class_ops {int dummy; } ;
struct module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rtc_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  devm_rtc_device_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct rtc_device**) ; 
 struct rtc_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct rtc_device**) ; 
 struct rtc_device* rtc_device_register (char const*,struct device*,struct rtc_class_ops const*,struct module*) ; 

struct rtc_device *devm_rtc_device_register(struct device *dev,
					const char *name,
					const struct rtc_class_ops *ops,
					struct module *owner)
{
	struct rtc_device **ptr, *rtc;

	ptr = devres_alloc(devm_rtc_device_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	rtc = rtc_device_register(name, dev, ops, owner);
	if (!IS_ERR(rtc)) {
		*ptr = rtc;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return rtc;
}