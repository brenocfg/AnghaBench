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
struct pcmcia_socket {int /*<<< orphan*/  ops_mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int ADD_MANAGED_RESOURCE ; 
 int EINVAL ; 
 unsigned int REMOVE_MANAGED_RESOURCE ; 
 int adjust_io (struct pcmcia_socket*,unsigned int,unsigned long,unsigned long) ; 
 struct pcmcia_socket* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static ssize_t store_io_db(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct pcmcia_socket *s = dev_get_drvdata(dev);
	unsigned long start_addr, end_addr;
	unsigned int add = ADD_MANAGED_RESOURCE;
	ssize_t ret = 0;

	ret = sscanf(buf, "+ 0x%lx - 0x%lx", &start_addr, &end_addr);
	if (ret != 2) {
		ret = sscanf(buf, "- 0x%lx - 0x%lx", &start_addr, &end_addr);
		add = REMOVE_MANAGED_RESOURCE;
		if (ret != 2) {
			ret = sscanf(buf, "0x%lx - 0x%lx", &start_addr,
				&end_addr);
			add = ADD_MANAGED_RESOURCE;
			if (ret != 2)
				return -EINVAL;
		}
	}
	if (end_addr < start_addr)
		return -EINVAL;

	mutex_lock(&s->ops_mutex);
	ret = adjust_io(s, add, start_addr, end_addr);
	mutex_unlock(&s->ops_mutex);

	return ret ? ret : count;
}