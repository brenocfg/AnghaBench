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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int HIBERNATION_FIRST ; 
 int HIBERNATION_INVALID ; 
 int HIBERNATION_MAX ; 
#define  HIBERNATION_PLATFORM 132 
#define  HIBERNATION_REBOOT 131 
#define  HIBERNATION_SHUTDOWN 130 
#define  HIBERNATION_SUSPEND 129 
#define  HIBERNATION_TEST_RESUME 128 
 int /*<<< orphan*/  hibernation_available () ; 
 int hibernation_mode ; 
 int /*<<< orphan*/ * hibernation_modes ; 
 int /*<<< orphan*/  hibernation_ops ; 
 int /*<<< orphan*/  lock_system_sleep () ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  pm_pr_dbg (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock_system_sleep () ; 

__attribute__((used)) static ssize_t disk_store(struct kobject *kobj, struct kobj_attribute *attr,
			  const char *buf, size_t n)
{
	int error = 0;
	int i;
	int len;
	char *p;
	int mode = HIBERNATION_INVALID;

	if (!hibernation_available())
		return -EPERM;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

	lock_system_sleep();
	for (i = HIBERNATION_FIRST; i <= HIBERNATION_MAX; i++) {
		if (len == strlen(hibernation_modes[i])
		    && !strncmp(buf, hibernation_modes[i], len)) {
			mode = i;
			break;
		}
	}
	if (mode != HIBERNATION_INVALID) {
		switch (mode) {
		case HIBERNATION_SHUTDOWN:
		case HIBERNATION_REBOOT:
#ifdef CONFIG_SUSPEND
		case HIBERNATION_SUSPEND:
#endif
		case HIBERNATION_TEST_RESUME:
			hibernation_mode = mode;
			break;
		case HIBERNATION_PLATFORM:
			if (hibernation_ops)
				hibernation_mode = mode;
			else
				error = -EINVAL;
		}
	} else
		error = -EINVAL;

	if (!error)
		pm_pr_dbg("Hibernation mode set to '%s'\n",
			       hibernation_modes[mode]);
	unlock_system_sleep();
	return error ? error : n;
}