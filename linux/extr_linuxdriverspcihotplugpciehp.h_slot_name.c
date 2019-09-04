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
struct slot {int /*<<< orphan*/  hotplug_slot; } ;

/* Variables and functions */
 char const* hotplug_slot_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *slot_name(struct slot *slot)
{
	return hotplug_slot_name(slot->hotplug_slot);
}