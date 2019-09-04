#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct touchpad_control {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {char* name; int mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  store; int /*<<< orphan*/  show; TYPE_2__ attr; } ;
struct TYPE_6__ {unsigned int handle; TYPE_5__ attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int device_create_file (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sony_nc_touchpad_show ; 
 int /*<<< orphan*/  sony_nc_touchpad_store ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 
 TYPE_1__* tp_ctl ; 

__attribute__((used)) static int sony_nc_touchpad_setup(struct platform_device *pd,
		unsigned int handle)
{
	int ret = 0;

	tp_ctl = kzalloc(sizeof(struct touchpad_control), GFP_KERNEL);
	if (!tp_ctl)
		return -ENOMEM;

	tp_ctl->handle = handle;

	sysfs_attr_init(&tp_ctl->attr.attr);
	tp_ctl->attr.attr.name = "touchpad";
	tp_ctl->attr.attr.mode = S_IRUGO | S_IWUSR;
	tp_ctl->attr.show = sony_nc_touchpad_show;
	tp_ctl->attr.store = sony_nc_touchpad_store;

	ret = device_create_file(&pd->dev, &tp_ctl->attr);
	if (ret) {
		kfree(tp_ctl);
		tp_ctl = NULL;
	}

	return ret;
}