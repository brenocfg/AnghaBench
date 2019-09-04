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
typedef  int /*<<< orphan*/  profiler_name_store_t ;
struct TYPE_2__ {int /*<<< orphan*/ * name_store; } ;

/* Variables and functions */
 TYPE_1__* obs ; 

profiler_name_store_t *obs_get_profiler_name_store(void)
{
	if (!obs)
		return NULL;

	return obs->name_store;
}