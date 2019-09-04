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
struct w1_master {long search_count; int /*<<< orphan*/  thread; int /*<<< orphan*/  mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct w1_master* dev_to_w1_master (struct device*) ; 
 int kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t w1_master_attribute_store_search(struct device * dev,
						struct device_attribute *attr,
						const char * buf, size_t count)
{
	long tmp;
	struct w1_master *md = dev_to_w1_master(dev);
	int ret;

	ret = kstrtol(buf, 0, &tmp);
	if (ret)
		return ret;

	mutex_lock(&md->mutex);
	md->search_count = tmp;
	mutex_unlock(&md->mutex);
	/* Only wake if it is going to be searching. */
	if (tmp)
		wake_up_process(md->thread);

	return count;
}