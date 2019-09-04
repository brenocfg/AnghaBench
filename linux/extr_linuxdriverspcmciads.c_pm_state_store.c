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
struct pcmcia_device {scalar_t__ suspended; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int runtime_resume (struct device*) ; 
 int runtime_suspend (struct device*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct pcmcia_device* to_pcmcia_dev (struct device*) ; 

__attribute__((used)) static ssize_t pm_state_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct pcmcia_device *p_dev = to_pcmcia_dev(dev);
	int ret = 0;

	if (!count)
		return -EINVAL;

	if ((!p_dev->suspended) && !strncmp(buf, "off", 3))
		ret = runtime_suspend(dev);
	else if (p_dev->suspended && !strncmp(buf, "on", 2))
		ret = runtime_resume(dev);

	return ret ? ret : count;
}