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
struct visor_device {int /*<<< orphan*/  visorchannel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int LINESIZE ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct visor_device* to_visor_device (struct device*) ; 
 char* visorchannel_id (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t typeguid_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct visor_device *vdev = to_visor_device(dev);
	char typeid[LINESIZE];

	return sprintf(buf, "%s\n",
		       visorchannel_id(vdev->visorchannel, typeid));
}