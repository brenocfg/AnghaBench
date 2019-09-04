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
struct typec_plug {size_t index; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct typec_altmode {TYPE_1__ dev; } ;
struct altmode {struct altmode* partner; int /*<<< orphan*/ ** plug; struct typec_altmode adev; } ;

/* Variables and functions */
 scalar_t__ is_typec_plug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 struct typec_plug* to_typec_plug (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void typec_altmode_put_partner(struct altmode *altmode)
{
	struct altmode *partner = altmode->partner;
	struct typec_altmode *adev;

	if (!partner)
		return;

	adev = &partner->adev;

	if (is_typec_plug(adev->dev.parent)) {
		struct typec_plug *plug = to_typec_plug(adev->dev.parent);

		partner->plug[plug->index] = NULL;
	} else {
		partner->partner = NULL;
	}
	put_device(&adev->dev);
}