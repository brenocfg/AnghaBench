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
struct omapfb_device {TYPE_1__* ctrl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct omapfb_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t omapfb_show_ctrl_name(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct omapfb_device *fbdev = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE, "%s\n", fbdev->ctrl->name);
}