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
struct TYPE_2__ {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FATAL ; 
 TYPE_1__** active_timeouts ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int) ; 
 int num_active_timeouts ; 

__attribute__((used)) static void
remove_timeout_index(int index)
{
	int			i;

	if (index < 0 || index >= num_active_timeouts)
		elog(FATAL, "timeout index %d out of range 0..%d", index,
			 num_active_timeouts - 1);

	Assert(active_timeouts[index]->active);
	active_timeouts[index]->active = false;

	for (i = index + 1; i < num_active_timeouts; i++)
		active_timeouts[i - 1] = active_timeouts[i];

	num_active_timeouts--;
}