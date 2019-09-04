#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct powercap_control_type_ops {int /*<<< orphan*/  release; } ;
struct TYPE_3__ {int /*<<< orphan*/ * class; } ;
struct powercap_control_type {int allocated; int /*<<< orphan*/  node; int /*<<< orphan*/  idr; TYPE_1__ dev; struct powercap_control_type_ops const* ops; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct powercap_control_type* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,char const*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct powercap_control_type*) ; 
 struct powercap_control_type* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct powercap_control_type*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powercap_class ; 
 int /*<<< orphan*/  powercap_cntrl_list ; 
 int /*<<< orphan*/  powercap_cntrl_list_lock ; 

struct powercap_control_type *powercap_register_control_type(
				struct powercap_control_type *control_type,
				const char *name,
				const struct powercap_control_type_ops *ops)
{
	int result;

	if (!name)
		return ERR_PTR(-EINVAL);
	if (control_type) {
		if (!ops || !ops->release)
			return ERR_PTR(-EINVAL);
		memset(control_type, 0, sizeof(*control_type));
	} else {
		control_type = kzalloc(sizeof(*control_type), GFP_KERNEL);
		if (!control_type)
			return ERR_PTR(-ENOMEM);
		control_type->allocated = true;
	}
	mutex_init(&control_type->lock);
	control_type->ops = ops;
	INIT_LIST_HEAD(&control_type->node);
	control_type->dev.class = &powercap_class;
	dev_set_name(&control_type->dev, "%s", name);
	result = device_register(&control_type->dev);
	if (result) {
		if (control_type->allocated)
			kfree(control_type);
		return ERR_PTR(result);
	}
	idr_init(&control_type->idr);

	mutex_lock(&powercap_cntrl_list_lock);
	list_add_tail(&control_type->node, &powercap_cntrl_list);
	mutex_unlock(&powercap_cntrl_list_lock);

	return control_type;
}