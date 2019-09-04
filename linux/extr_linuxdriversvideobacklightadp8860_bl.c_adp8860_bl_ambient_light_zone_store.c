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
typedef  unsigned long uint8_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adp8860_bl {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADP8860_CFGR ; 
 int /*<<< orphan*/  ADP8860_MDCR ; 
 unsigned long CFGR_BLV_MASK ; 
 unsigned long CFGR_BLV_SHIFT ; 
 int /*<<< orphan*/  CMP_AUTOEN ; 
 int /*<<< orphan*/  adp8860_clr_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adp8860_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  adp8860_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp8860_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct adp8860_bl* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t adp8860_bl_ambient_light_zone_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct adp8860_bl *data = dev_get_drvdata(dev);
	unsigned long val;
	uint8_t reg_val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	if (val == 0) {
		/* Enable automatic ambient light sensing */
		adp8860_set_bits(data->client, ADP8860_MDCR, CMP_AUTOEN);
	} else if ((val > 0) && (val <= 3)) {
		/* Disable automatic ambient light sensing */
		adp8860_clr_bits(data->client, ADP8860_MDCR, CMP_AUTOEN);

		/* Set user supplied ambient light zone */
		mutex_lock(&data->lock);
		ret = adp8860_read(data->client, ADP8860_CFGR, &reg_val);
		if (!ret) {
			reg_val &= ~(CFGR_BLV_MASK << CFGR_BLV_SHIFT);
			reg_val |= (val - 1) << CFGR_BLV_SHIFT;
			adp8860_write(data->client, ADP8860_CFGR, reg_val);
		}
		mutex_unlock(&data->lock);
	}

	return count;
}