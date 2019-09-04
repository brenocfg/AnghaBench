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
struct TYPE_3__ {int member_0; int /*<<< orphan*/  ullAvailPhys; } ;
typedef  TYPE_1__ MEMORYSTATUSEX ;

/* Variables and functions */
 int /*<<< orphan*/  os_get_sys_memory_usage_internal (TYPE_1__*) ; 

uint64_t os_get_sys_free_size(void)
{
	MEMORYSTATUSEX msex = {sizeof(MEMORYSTATUSEX)};
	if (!os_get_sys_memory_usage_internal(&msex))
		return 0;
	return msex.ullAvailPhys;
}