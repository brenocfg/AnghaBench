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
typedef  int u8 ;
struct lm3533_bl {int /*<<< orphan*/  lm3533; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM3533_REG_CTRLBANK_AB_BCONF ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lm3533_bl* dev_get_drvdata (struct device*) ; 
 int lm3533_bl_get_ctrlbank_id (struct lm3533_bl*) ; 
 int lm3533_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t show_als_en(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct lm3533_bl *bl = dev_get_drvdata(dev);
	int ctrlbank = lm3533_bl_get_ctrlbank_id(bl);
	u8 val;
	u8 mask;
	bool enable;
	int ret;

	ret = lm3533_read(bl->lm3533, LM3533_REG_CTRLBANK_AB_BCONF, &val);
	if (ret)
		return ret;

	mask = 1 << (2 * ctrlbank);
	enable = val & mask;

	return scnprintf(buf, PAGE_SIZE, "%d\n", enable);
}