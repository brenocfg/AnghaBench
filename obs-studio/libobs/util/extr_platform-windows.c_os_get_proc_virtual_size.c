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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int member_0; int /*<<< orphan*/  PagefileUsage; } ;
typedef  TYPE_1__ PROCESS_MEMORY_COUNTERS ;

/* Variables and functions */
 int /*<<< orphan*/  os_get_proc_memory_usage_internal (TYPE_1__*) ; 

uint64_t os_get_proc_virtual_size(void)
{
	PROCESS_MEMORY_COUNTERS pmc = {sizeof(PROCESS_MEMORY_COUNTERS)};
	if (!os_get_proc_memory_usage_internal(&pmc))
		return 0;
	return pmc.PagefileUsage;
}