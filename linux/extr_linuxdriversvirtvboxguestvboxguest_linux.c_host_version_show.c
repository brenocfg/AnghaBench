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
struct vbg_dev {char* host_version; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct vbg_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t host_version_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct vbg_dev *gdev = dev_get_drvdata(dev);

	return sprintf(buf, "%s\n", gdev->host_version);
}