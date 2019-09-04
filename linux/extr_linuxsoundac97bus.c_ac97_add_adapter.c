#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; int /*<<< orphan*/ * type; } ;
struct ac97_controller {int nr; int /*<<< orphan*/  parent; TYPE_1__ adap; int /*<<< orphan*/  controllers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ac97_adapter_idr ; 
 int /*<<< orphan*/  ac97_adapter_type ; 
 int /*<<< orphan*/  ac97_controllers ; 
 int /*<<< orphan*/  ac97_controllers_mutex ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_register (TYPE_1__*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct ac97_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int ac97_add_adapter(struct ac97_controller *ac97_ctrl)
{
	int ret;

	mutex_lock(&ac97_controllers_mutex);
	ret = idr_alloc(&ac97_adapter_idr, ac97_ctrl, 0, 0, GFP_KERNEL);
	ac97_ctrl->nr = ret;
	if (ret >= 0) {
		dev_set_name(&ac97_ctrl->adap, "ac97-%d", ret);
		ac97_ctrl->adap.type = &ac97_adapter_type;
		ac97_ctrl->adap.parent = ac97_ctrl->parent;
		ret = device_register(&ac97_ctrl->adap);
		if (ret)
			put_device(&ac97_ctrl->adap);
	}
	if (!ret)
		list_add(&ac97_ctrl->controllers, &ac97_controllers);
	mutex_unlock(&ac97_controllers_mutex);

	if (!ret)
		dev_dbg(&ac97_ctrl->adap, "adapter registered by %s\n",
			dev_name(ac97_ctrl->parent));
	return ret;
}