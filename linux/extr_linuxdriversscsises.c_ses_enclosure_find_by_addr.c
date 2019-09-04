#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ses_component {scalar_t__ addr; } ;
struct enclosure_device {int components; TYPE_1__* component; } ;
struct efd {scalar_t__ addr; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {struct ses_component* scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 scalar_t__ enclosure_add_device (struct enclosure_device*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ses_enclosure_find_by_addr(struct enclosure_device *edev,
				      void *data)
{
	struct efd *efd = data;
	int i;
	struct ses_component *scomp;

	if (!edev->component[0].scratch)
		return 0;

	for (i = 0; i < edev->components; i++) {
		scomp = edev->component[i].scratch;
		if (scomp->addr != efd->addr)
			continue;

		if (enclosure_add_device(edev, i, efd->dev) == 0)
			kobject_uevent(&efd->dev->kobj, KOBJ_CHANGE);
		return 1;
	}
	return 0;
}