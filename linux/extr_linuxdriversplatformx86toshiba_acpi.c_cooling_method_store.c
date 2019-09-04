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
struct toshiba_acpi_dev {int max_cooling_method; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct toshiba_acpi_dev* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int toshiba_cooling_method_set (struct toshiba_acpi_dev*,int) ; 

__attribute__((used)) static ssize_t cooling_method_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	int state;
	int ret;

	ret = kstrtoint(buf, 0, &state);
	if (ret)
		return ret;

	/*
	 * Check for supported values
	 * Depending on the laptop model, some only support these two:
	 * 0 - Maximum Performance
	 * 1 - Battery Optimized
	 *
	 * While some others support all three methods:
	 * 0 - Maximum Performance
	 * 1 - Performance
	 * 2 - Battery Optimized
	 */
	if (state < 0 || state > toshiba->max_cooling_method)
		return -EINVAL;

	ret = toshiba_cooling_method_set(toshiba, state);
	if (ret)
		return ret;

	return count;
}