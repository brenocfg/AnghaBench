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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int slaves; } ;
struct cpsw_common {TYPE_3__* slaves; TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__* phy; } ;
struct TYPE_5__ {scalar_t__ speed; scalar_t__ link; } ;

/* Variables and functions */

__attribute__((used)) static int cpsw_get_common_speed(struct cpsw_common *cpsw)
{
	int i, speed;

	for (i = 0, speed = 0; i < cpsw->data.slaves; i++)
		if (cpsw->slaves[i].phy && cpsw->slaves[i].phy->link)
			speed += cpsw->slaves[i].phy->speed;

	return speed;
}