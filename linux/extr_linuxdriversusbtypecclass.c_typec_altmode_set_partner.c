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
struct typec_port {int /*<<< orphan*/  dev; } ;
struct typec_plug {size_t index; } ;
struct typec_device_id {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct typec_altmode {TYPE_1__ dev; int /*<<< orphan*/  mode; int /*<<< orphan*/  svid; } ;
struct device {int dummy; } ;
struct altmode {struct altmode* partner; struct altmode** plug; struct typec_altmode adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  altmode_match ; 
 struct device* device_find_child (int /*<<< orphan*/ *,struct typec_device_id*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_typec_plug (int /*<<< orphan*/ ) ; 
 struct altmode* to_altmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_typec_altmode (struct device*) ; 
 struct typec_plug* to_typec_plug (int /*<<< orphan*/ ) ; 
 struct typec_port* typec_altmode2port (struct typec_altmode*) ; 

__attribute__((used)) static void typec_altmode_set_partner(struct altmode *altmode)
{
	struct typec_altmode *adev = &altmode->adev;
	struct typec_device_id id = { adev->svid, adev->mode, };
	struct typec_port *port = typec_altmode2port(adev);
	struct altmode *partner;
	struct device *dev;

	dev = device_find_child(&port->dev, &id, altmode_match);
	if (!dev)
		return;

	/* Bind the port alt mode to the partner/plug alt mode. */
	partner = to_altmode(to_typec_altmode(dev));
	altmode->partner = partner;

	/* Bind the partner/plug alt mode to the port alt mode. */
	if (is_typec_plug(adev->dev.parent)) {
		struct typec_plug *plug = to_typec_plug(adev->dev.parent);

		partner->plug[plug->index] = altmode;
	} else {
		partner->partner = altmode;
	}
}