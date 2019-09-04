#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  store; int /*<<< orphan*/ * show; TYPE_1__ attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_IWUSR ; 
 unsigned int device_create_file (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* sc_handle ; 
 int /*<<< orphan*/  sony_nc_smart_conn_store ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_1__*) ; 

__attribute__((used)) static int sony_nc_smart_conn_setup(struct platform_device *pd)
{
	unsigned int result;

	sc_handle = kzalloc(sizeof(struct device_attribute), GFP_KERNEL);
	if (!sc_handle)
		return -ENOMEM;

	sysfs_attr_init(&sc_handle->attr);
	sc_handle->attr.name = "smart_connect";
	sc_handle->attr.mode = S_IWUSR;
	sc_handle->show = NULL;
	sc_handle->store = sony_nc_smart_conn_store;

	result = device_create_file(&pd->dev, sc_handle);
	if (result) {
		kfree(sc_handle);
		sc_handle = NULL;
		return result;
	}

	return 0;
}