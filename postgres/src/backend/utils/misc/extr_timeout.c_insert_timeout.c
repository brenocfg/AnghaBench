#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t TimeoutId ;
struct TYPE_3__ {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FATAL ; 
 TYPE_1__** active_timeouts ; 
 TYPE_1__* all_timeouts ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int) ; 
 int num_active_timeouts ; 

__attribute__((used)) static void
insert_timeout(TimeoutId id, int index)
{
	int			i;

	if (index < 0 || index > num_active_timeouts)
		elog(FATAL, "timeout index %d out of range 0..%d", index,
			 num_active_timeouts);

	Assert(!all_timeouts[id].active);
	all_timeouts[id].active = true;

	for (i = num_active_timeouts - 1; i >= index; i--)
		active_timeouts[i + 1] = active_timeouts[i];

	active_timeouts[index] = &all_timeouts[id];

	num_active_timeouts++;
}