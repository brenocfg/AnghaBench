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
struct rfkill {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_global_mutex ; 
 int /*<<< orphan*/  rfkill_set_block (struct rfkill*,unsigned long) ; 
 struct rfkill* to_rfkill (struct device*) ; 

__attribute__((used)) static ssize_t soft_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct rfkill *rfkill = to_rfkill(dev);
	unsigned long state;
	int err;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	err = kstrtoul(buf, 0, &state);
	if (err)
		return err;

	if (state > 1 )
		return -EINVAL;

	mutex_lock(&rfkill_global_mutex);
	rfkill_set_block(rfkill, state);
	mutex_unlock(&rfkill_global_mutex);

	return count;
}