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
struct ac97_controller {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct ac97_controller*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ac97_controller*) ; 

__attribute__((used)) static int ac97_bus_reset(struct ac97_controller *ac97_ctrl)
{
	ac97_ctrl->ops->reset(ac97_ctrl);

	return 0;
}