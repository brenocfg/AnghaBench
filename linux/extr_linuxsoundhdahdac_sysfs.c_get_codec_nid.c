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
struct kobject {int /*<<< orphan*/  name; TYPE_1__* parent; } ;
struct hdac_device {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct hdac_device* dev_to_hdac_dev (struct device*) ; 
 struct device* kobj_to_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoint (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int get_codec_nid(struct kobject *kobj, struct hdac_device **codecp)
{
	struct device *dev = kobj_to_dev(kobj->parent->parent);
	int nid;
	ssize_t ret;

	ret = kstrtoint(kobj->name, 16, &nid);
	if (ret < 0)
		return ret;
	*codecp = dev_to_hdac_dev(dev);
	return nid;
}