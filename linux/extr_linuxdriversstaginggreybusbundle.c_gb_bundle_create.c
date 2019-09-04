#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int /*<<< orphan*/  dma_mask; } ;
struct gb_interface {int /*<<< orphan*/  bundles; TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; TYPE_3__* parent; } ;
struct gb_bundle {int /*<<< orphan*/  links; TYPE_1__ dev; int /*<<< orphan*/  connections; scalar_t__ class; scalar_t__ id; struct gb_interface* intf; } ;

/* Variables and functions */
 scalar_t__ BUNDLE_ID_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bundle_groups ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 scalar_t__ gb_bundle_find (struct gb_interface*,scalar_t__) ; 
 int /*<<< orphan*/  greybus_bundle_type ; 
 int /*<<< orphan*/  greybus_bus_type ; 
 struct gb_bundle* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_bundle_create (struct gb_bundle*) ; 

struct gb_bundle *gb_bundle_create(struct gb_interface *intf, u8 bundle_id,
				   u8 class)
{
	struct gb_bundle *bundle;

	if (bundle_id == BUNDLE_ID_NONE) {
		dev_err(&intf->dev, "can't use bundle id %u\n", bundle_id);
		return NULL;
	}

	/*
	 * Reject any attempt to reuse a bundle id.  We initialize
	 * these serially, so there's no need to worry about keeping
	 * the interface bundle list locked here.
	 */
	if (gb_bundle_find(intf, bundle_id)) {
		dev_err(&intf->dev, "duplicate bundle id %u\n", bundle_id);
		return NULL;
	}

	bundle = kzalloc(sizeof(*bundle), GFP_KERNEL);
	if (!bundle)
		return NULL;

	bundle->intf = intf;
	bundle->id = bundle_id;
	bundle->class = class;
	INIT_LIST_HEAD(&bundle->connections);

	bundle->dev.parent = &intf->dev;
	bundle->dev.bus = &greybus_bus_type;
	bundle->dev.type = &greybus_bundle_type;
	bundle->dev.groups = bundle_groups;
	bundle->dev.dma_mask = intf->dev.dma_mask;
	device_initialize(&bundle->dev);
	dev_set_name(&bundle->dev, "%s.%d", dev_name(&intf->dev), bundle_id);

	list_add(&bundle->links, &intf->bundles);

	trace_gb_bundle_create(bundle);

	return bundle;
}