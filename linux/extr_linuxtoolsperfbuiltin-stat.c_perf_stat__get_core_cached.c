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
 int perf_stat__get_aggr (int /*<<< orphan*/ ,struct cpu_map*,int) ; 
 int /*<<< orphan*/  perf_stat__get_core ; 

__attribute__((used)) static int perf_stat__get_core_cached(struct cpu_map *map, int idx)
{
	return perf_stat__get_aggr(perf_stat__get_core, map, idx);
}