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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_system_sleep () ; 
 scalar_t__ name_to_dev_t (char*) ; 
 scalar_t__ noresume ; 
 int /*<<< orphan*/  pm_pr_dbg (char*,scalar_t__) ; 
 int /*<<< orphan*/  software_resume () ; 
 scalar_t__ swsusp_resume_device ; 
 int /*<<< orphan*/  unlock_system_sleep () ; 

__attribute__((used)) static ssize_t resume_store(struct kobject *kobj, struct kobj_attribute *attr,
			    const char *buf, size_t n)
{
	dev_t res;
	int len = n;
	char *name;

	if (len && buf[len-1] == '\n')
		len--;
	name = kstrndup(buf, len, GFP_KERNEL);
	if (!name)
		return -ENOMEM;

	res = name_to_dev_t(name);
	kfree(name);
	if (!res)
		return -EINVAL;

	lock_system_sleep();
	swsusp_resume_device = res;
	unlock_system_sleep();
	pm_pr_dbg("Configured resume from disk to %u\n", swsusp_resume_device);
	noresume = 0;
	software_resume();
	return n;
}