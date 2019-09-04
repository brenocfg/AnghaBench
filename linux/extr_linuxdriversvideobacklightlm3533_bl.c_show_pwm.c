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
typedef  int /*<<< orphan*/  u8 ;
struct lm3533_bl {int /*<<< orphan*/  cb; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lm3533_bl* dev_get_drvdata (struct device*) ; 
 int lm3533_ctrlbank_get_pwm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_pwm(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct lm3533_bl *bl = dev_get_drvdata(dev);
	u8 val;
	int ret;

	ret = lm3533_ctrlbank_get_pwm(&bl->cb, &val);
	if (ret)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "%u\n", val);
}