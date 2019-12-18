#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {TYPE_1__ children; } ;
typedef  TYPE_2__ profiler_snapshot_entry_t ;
typedef  int /*<<< orphan*/  (* profiler_entry_enum_func ) (void*,int /*<<< orphan*/ *) ;

/* Variables and functions */

void profiler_snapshot_enumerate_children(profiler_snapshot_entry_t *entry,
					  profiler_entry_enum_func func,
					  void *context)
{
	if (!entry)
		return;

	for (size_t i = 0; i < entry->children.num; i++)
		if (!func(context, &entry->children.array[i]))
			break;
}