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
struct lp855x {scalar_t__ mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PWM_BASED ; 
 scalar_t__ REGISTER_BASED ; 
 struct lp855x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t lp855x_get_bl_ctl_mode(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct lp855x *lp = dev_get_drvdata(dev);
	char *strmode = NULL;

	if (lp->mode == PWM_BASED)
		strmode = "pwm based";
	else if (lp->mode == REGISTER_BASED)
		strmode = "register based";

	return scnprintf(buf, PAGE_SIZE, "%s\n", strmode);
}