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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  dma_mask; } ;
struct gb_module {TYPE_4__ dev; struct gb_host_device* hd; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; TYPE_4__* parent; } ;
struct gb_interface {TYPE_1__ dev; int /*<<< orphan*/  device_id; int /*<<< orphan*/  mode_switch_completion; int /*<<< orphan*/  mode_switch_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  manifest_descs; int /*<<< orphan*/  bundles; int /*<<< orphan*/  interface_id; struct gb_module* module; struct gb_host_device* hd; } ;
struct gb_host_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_INTERFACE_AUTOSUSPEND_MS ; 
 int /*<<< orphan*/  GB_INTERFACE_DEVICE_ID_BAD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  gb_interface_mode_switch_work ; 
 int /*<<< orphan*/  greybus_bus_type ; 
 int /*<<< orphan*/  greybus_interface_type ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_groups ; 
 struct gb_interface* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_interface_create (struct gb_interface*) ; 

struct gb_interface *gb_interface_create(struct gb_module *module,
					 u8 interface_id)
{
	struct gb_host_device *hd = module->hd;
	struct gb_interface *intf;

	intf = kzalloc(sizeof(*intf), GFP_KERNEL);
	if (!intf)
		return NULL;

	intf->hd = hd;		/* XXX refcount? */
	intf->module = module;
	intf->interface_id = interface_id;
	INIT_LIST_HEAD(&intf->bundles);
	INIT_LIST_HEAD(&intf->manifest_descs);
	mutex_init(&intf->mutex);
	INIT_WORK(&intf->mode_switch_work, gb_interface_mode_switch_work);
	init_completion(&intf->mode_switch_completion);

	/* Invalid device id to start with */
	intf->device_id = GB_INTERFACE_DEVICE_ID_BAD;

	intf->dev.parent = &module->dev;
	intf->dev.bus = &greybus_bus_type;
	intf->dev.type = &greybus_interface_type;
	intf->dev.groups = interface_groups;
	intf->dev.dma_mask = module->dev.dma_mask;
	device_initialize(&intf->dev);
	dev_set_name(&intf->dev, "%s.%u", dev_name(&module->dev),
		     interface_id);

	pm_runtime_set_autosuspend_delay(&intf->dev,
					 GB_INTERFACE_AUTOSUSPEND_MS);

	trace_gb_interface_create(intf);

	return intf;
}