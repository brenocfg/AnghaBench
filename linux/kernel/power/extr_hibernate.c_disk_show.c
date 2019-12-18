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
 int HIBERNATION_FIRST ; 
 int HIBERNATION_MAX ; 
#define  HIBERNATION_PLATFORM 132 
#define  HIBERNATION_REBOOT 131 
#define  HIBERNATION_SHUTDOWN 130 
#define  HIBERNATION_SUSPEND 129 
#define  HIBERNATION_TEST_RESUME 128 
 int /*<<< orphan*/  hibernation_available () ; 
 int hibernation_mode ; 
 char** hibernation_modes ; 
 int /*<<< orphan*/  hibernation_ops ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t disk_show(struct kobject *kobj, struct kobj_attribute *attr,
			 char *buf)
{
	int i;
	char *start = buf;

	if (!hibernation_available())
		return sprintf(buf, "[disabled]\n");

	for (i = HIBERNATION_FIRST; i <= HIBERNATION_MAX; i++) {
		if (!hibernation_modes[i])
			continue;
		switch (i) {
		case HIBERNATION_SHUTDOWN:
		case HIBERNATION_REBOOT:
#ifdef CONFIG_SUSPEND
		case HIBERNATION_SUSPEND:
#endif
		case HIBERNATION_TEST_RESUME:
			break;
		case HIBERNATION_PLATFORM:
			if (hibernation_ops)
				break;
			/* not a valid mode, continue with loop */
			continue;
		}
		if (i == hibernation_mode)
			buf += sprintf(buf, "[%s] ", hibernation_modes[i]);
		else
			buf += sprintf(buf, "%s ", hibernation_modes[i]);
	}
	buf += sprintf(buf, "\n");
	return buf-start;
}