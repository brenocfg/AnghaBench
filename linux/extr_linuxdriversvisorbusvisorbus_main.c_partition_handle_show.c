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
typedef  int /*<<< orphan*/  u64 ;
struct visor_device {int /*<<< orphan*/  visorchannel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct visor_device* to_visor_device (struct device*) ; 
 int /*<<< orphan*/  visorchannel_get_clientpartition (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t partition_handle_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct visor_device *vdev = to_visor_device(dev);
	u64 handle = visorchannel_get_clientpartition(vdev->visorchannel);

	return sprintf(buf, "0x%llx\n", handle);
}