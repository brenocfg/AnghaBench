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
typedef  int /*<<< orphan*/  u8 ;
struct hotplug_slot {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  latch_status; } ;

/* Variables and functions */

__attribute__((used)) static int
get_latch_status(struct hotplug_slot *hotplug_slot, u8 *value)
{
	*value = hotplug_slot->info->latch_status;
	return 0;
}