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
struct rio_dev {TYPE_2__* rswitch; scalar_t__ em_efptr; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* em_init ) (struct rio_dev*) ;} ;

/* Variables and functions */
 scalar_t__ rio_is_switch (struct rio_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rio_dev*) ; 

__attribute__((used)) static void rio_init_em(struct rio_dev *rdev)
{
	if (rio_is_switch(rdev) && (rdev->em_efptr) &&
	    rdev->rswitch->ops && rdev->rswitch->ops->em_init) {
		rdev->rswitch->ops->em_init(rdev);
	}
}