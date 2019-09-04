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
struct iproc_gpio {unsigned int nr_pinconf_disable; int* pinconf_disable; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */

__attribute__((used)) static bool iproc_pinconf_param_is_disabled(struct iproc_gpio *chip,
					    enum pin_config_param param)
{
	unsigned int i;

	if (!chip->nr_pinconf_disable)
		return false;

	for (i = 0; i < chip->nr_pinconf_disable; i++)
		if (chip->pinconf_disable[i] == param)
			return true;

	return false;
}