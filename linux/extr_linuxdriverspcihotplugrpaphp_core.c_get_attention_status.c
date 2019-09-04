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
typedef  int /*<<< orphan*/  u8 ;
struct slot {TYPE_2__* hotplug_slot; } ;
struct hotplug_slot {scalar_t__ private; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {int /*<<< orphan*/  attention_status; } ;

/* Variables and functions */

__attribute__((used)) static int get_attention_status(struct hotplug_slot *hotplug_slot, u8 *value)
{
	struct slot *slot = (struct slot *)hotplug_slot->private;
	*value = slot->hotplug_slot->info->attention_status;
	return 0;
}