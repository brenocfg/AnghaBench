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
struct lm3533_bl {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lm3533_bl* dev_get_drvdata (struct device*) ; 
 unsigned int lm3533_bl_get_ctrlbank_id (struct lm3533_bl*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t show_als_channel(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct lm3533_bl *bl = dev_get_drvdata(dev);
	unsigned channel = lm3533_bl_get_ctrlbank_id(bl);

	return scnprintf(buf, PAGE_SIZE, "%u\n", channel);
}