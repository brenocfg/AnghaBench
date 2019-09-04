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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dcon_sleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t dcon_sleep_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	unsigned long output;
	int ret;

	ret = kstrtoul(buf, 10, &output);
	if (ret)
		return ret;

	dcon_sleep(dev_get_drvdata(dev), output ? true : false);
	return count;
}