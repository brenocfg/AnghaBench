#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct typec_altmode_driver {int /*<<< orphan*/  (* remove ) (struct typec_altmode*) ;} ;
struct typec_altmode {int /*<<< orphan*/ * ops; int /*<<< orphan*/ * desc; scalar_t__ active; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct altmode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_STATE_SAFE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct typec_altmode*) ; 
 struct altmode* to_altmode (struct typec_altmode*) ; 
 struct typec_altmode_driver* to_altmode_driver (int /*<<< orphan*/ ) ; 
 struct typec_altmode* to_typec_altmode (struct device*) ; 
 int /*<<< orphan*/  typec_altmode_remove_links (struct altmode*) ; 
 int /*<<< orphan*/  typec_altmode_set_state (struct typec_altmode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_altmode_update_active (struct typec_altmode*,int) ; 

__attribute__((used)) static int typec_remove(struct device *dev)
{
	struct typec_altmode_driver *drv = to_altmode_driver(dev->driver);
	struct typec_altmode *adev = to_typec_altmode(dev);
	struct altmode *altmode = to_altmode(adev);

	typec_altmode_remove_links(altmode);

	if (drv->remove)
		drv->remove(to_typec_altmode(dev));

	if (adev->active) {
		WARN_ON(typec_altmode_set_state(adev, TYPEC_STATE_SAFE));
		typec_altmode_update_active(adev, false);
	}

	adev->desc = NULL;
	adev->ops = NULL;

	return 0;
}