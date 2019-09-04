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
struct kobject {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int MTTY_STRING_LEN ; 
 char* dev_driver_string (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
name_show(struct kobject *kobj, struct device *dev, char *buf)
{
	char name[MTTY_STRING_LEN];
	int i;
	const char *name_str[2] = {"Single port serial", "Dual port serial"};

	for (i = 0; i < 2; i++) {
		snprintf(name, MTTY_STRING_LEN, "%s-%d",
			 dev_driver_string(dev), i + 1);
		if (!strcmp(kobj->name, name))
			return sprintf(buf, "%s\n", name_str[i]);
	}

	return -EINVAL;
}