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
struct cpu_map {int dummy; } ;

/* Variables and functions */
 int cpu_map__get_socket (struct cpu_map*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_stat__get_socket(struct cpu_map *map, int cpu)
{
	return cpu_map__get_socket(map, cpu, NULL);
}