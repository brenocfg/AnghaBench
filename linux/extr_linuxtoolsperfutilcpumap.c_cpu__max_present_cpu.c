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
 int max_present_cpu_num ; 
 int /*<<< orphan*/  set_max_cpu_num () ; 
 scalar_t__ unlikely (int) ; 

int cpu__max_present_cpu(void)
{
	if (unlikely(!max_present_cpu_num))
		set_max_cpu_num();

	return max_present_cpu_num;
}