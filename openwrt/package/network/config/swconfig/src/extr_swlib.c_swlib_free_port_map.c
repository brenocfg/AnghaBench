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
struct switch_dev {int ports; TYPE_1__* maps; } ;
struct TYPE_2__ {struct TYPE_2__* segment; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
swlib_free_port_map(struct switch_dev *dev)
{
	int i;

	if (!dev || !dev->maps)
		return;

	for (i = 0; i < dev->ports; i++)
		free(dev->maps[i].segment);
	free(dev->maps);
}