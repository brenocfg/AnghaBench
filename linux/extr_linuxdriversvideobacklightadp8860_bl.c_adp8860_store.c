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
struct adp8860_bl {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  adp8860_write (int /*<<< orphan*/ ,int,unsigned long) ; 
 struct adp8860_bl* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t adp8860_store(struct device *dev, const char *buf,
			 size_t count, int reg)
{
	struct adp8860_bl *data = dev_get_drvdata(dev);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	mutex_lock(&data->lock);
	adp8860_write(data->client, reg, val);
	mutex_unlock(&data->lock);

	return count;
}