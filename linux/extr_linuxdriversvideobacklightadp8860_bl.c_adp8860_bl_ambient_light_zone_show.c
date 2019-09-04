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
typedef  int uint8_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adp8860_bl {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADP8860_CFGR ; 
 int CFGR_BLV_MASK ; 
 int CFGR_BLV_SHIFT ; 
 int adp8860_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct adp8860_bl* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t adp8860_bl_ambient_light_zone_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct adp8860_bl *data = dev_get_drvdata(dev);
	int error;
	uint8_t reg_val;

	mutex_lock(&data->lock);
	error = adp8860_read(data->client, ADP8860_CFGR, &reg_val);
	mutex_unlock(&data->lock);

	if (error < 0)
		return error;

	return sprintf(buf, "%u\n",
		((reg_val >> CFGR_BLV_SHIFT) & CFGR_BLV_MASK) + 1);
}