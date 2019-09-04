#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num_buffers; } ;
struct most_channel {TYPE_1__ cfg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct most_channel* to_channel (struct device*) ; 

__attribute__((used)) static ssize_t set_number_of_buffers_store(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf,
					   size_t count)
{
	struct most_channel *c = to_channel(dev);
	int ret = kstrtou16(buf, 0, &c->cfg.num_buffers);

	if (ret)
		return ret;
	return count;
}