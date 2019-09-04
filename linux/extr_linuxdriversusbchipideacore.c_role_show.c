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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ci_hdrc {scalar_t__ role; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 scalar_t__ CI_ROLE_END ; 
 TYPE_1__* ci_role (struct ci_hdrc*) ; 
 struct ci_hdrc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t role_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct ci_hdrc *ci = dev_get_drvdata(dev);

	if (ci->role != CI_ROLE_END)
		return sprintf(buf, "%s\n", ci_role(ci)->name);

	return 0;
}