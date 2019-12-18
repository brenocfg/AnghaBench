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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct soundbus_dev {struct platform_device ofdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct soundbus_dev* to_soundbus_device (struct device*) ; 

__attribute__((used)) static ssize_t name_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct soundbus_dev *sdev = to_soundbus_device(dev);
	struct platform_device *of = &sdev->ofdev;

	return sprintf(buf, "%pOFn\n", of->dev.of_node);
}