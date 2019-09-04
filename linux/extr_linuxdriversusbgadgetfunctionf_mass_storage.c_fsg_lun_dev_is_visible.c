#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct kobject {int dummy; } ;
struct fsg_lun {scalar_t__ removable; scalar_t__ cdrom; } ;
struct device {int dummy; } ;
struct attribute {int mode; } ;
struct TYPE_4__ {struct attribute attr; } ;
struct TYPE_3__ {struct attribute attr; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 TYPE_2__ dev_attr_file ; 
 TYPE_1__ dev_attr_ro ; 
 struct fsg_lun* fsg_lun_from_dev (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static umode_t fsg_lun_dev_is_visible(struct kobject *kobj,
				      struct attribute *attr, int idx)
{
	struct device *dev = kobj_to_dev(kobj);
	struct fsg_lun *lun = fsg_lun_from_dev(dev);

	if (attr == &dev_attr_ro.attr)
		return lun->cdrom ? S_IRUGO : (S_IWUSR | S_IRUGO);
	if (attr == &dev_attr_file.attr)
		return lun->removable ? (S_IWUSR | S_IRUGO) : S_IRUGO;
	return attr->mode;
}