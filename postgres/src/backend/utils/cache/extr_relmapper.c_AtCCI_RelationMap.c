#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num_mappings; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_local_updates ; 
 int /*<<< orphan*/  active_shared_updates ; 
 int /*<<< orphan*/  merge_map_updates (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__ pending_local_updates ; 
 TYPE_1__ pending_shared_updates ; 

void
AtCCI_RelationMap(void)
{
	if (pending_shared_updates.num_mappings != 0)
	{
		merge_map_updates(&active_shared_updates,
						  &pending_shared_updates,
						  true);
		pending_shared_updates.num_mappings = 0;
	}
	if (pending_local_updates.num_mappings != 0)
	{
		merge_map_updates(&active_local_updates,
						  &pending_local_updates,
						  true);
		pending_local_updates.num_mappings = 0;
	}
}