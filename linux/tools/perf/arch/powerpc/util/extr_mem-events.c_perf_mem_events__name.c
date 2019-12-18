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

/* Variables and functions */
 int PERF_MEM_EVENTS__LOAD ; 

char *perf_mem_events__name(int i)
{
	if (i == PERF_MEM_EVENTS__LOAD)
		return (char *) "cpu/mem-loads/";

	return (char *) "cpu/mem-stores/";
}