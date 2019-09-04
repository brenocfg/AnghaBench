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
typedef  int u32 ;
struct switchtec_dev {TYPE_1__* mmio_sys_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  device_version; } ;

/* Variables and functions */
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct switchtec_dev* to_stdev (struct device*) ; 

__attribute__((used)) static ssize_t device_version_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct switchtec_dev *stdev = to_stdev(dev);
	u32 ver;

	ver = ioread32(&stdev->mmio_sys_info->device_version);

	return sprintf(buf, "%x\n", ver);
}