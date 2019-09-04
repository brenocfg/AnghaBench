#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct typec_plug_desc {int index; } ;
struct TYPE_5__ {int /*<<< orphan*/ * type; TYPE_4__* parent; int /*<<< orphan*/  class; } ;
struct typec_plug {int index; TYPE_1__ dev; int /*<<< orphan*/  mode_ids; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct typec_cable {TYPE_4__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct typec_plug* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,char*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 struct typec_plug* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  typec_class ; 
 int /*<<< orphan*/  typec_plug_dev_type ; 

struct typec_plug *typec_register_plug(struct typec_cable *cable,
				       struct typec_plug_desc *desc)
{
	struct typec_plug *plug;
	char name[8];
	int ret;

	plug = kzalloc(sizeof(*plug), GFP_KERNEL);
	if (!plug)
		return ERR_PTR(-ENOMEM);

	sprintf(name, "plug%d", desc->index);

	ida_init(&plug->mode_ids);
	plug->index = desc->index;
	plug->dev.class = typec_class;
	plug->dev.parent = &cable->dev;
	plug->dev.type = &typec_plug_dev_type;
	dev_set_name(&plug->dev, "%s-%s", dev_name(cable->dev.parent), name);

	ret = device_register(&plug->dev);
	if (ret) {
		dev_err(&cable->dev, "failed to register plug (%d)\n", ret);
		put_device(&plug->dev);
		return ERR_PTR(ret);
	}

	return plug;
}