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
 int parse_int_file (int /*<<< orphan*/ ,char*,int) ; 

int get_physical_package_id(int cpu)
{
	return parse_int_file(
		0, "/sys/devices/system/cpu/cpu%d/topology/physical_package_id",
		cpu);
}