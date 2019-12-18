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
struct perf_record_record_cpu_map {int dummy; } ;
struct perf_record_cpu_map_data {scalar_t__ type; scalar_t__ data; } ;
struct perf_cpu_map {int dummy; } ;
struct cpu_map_entries {int dummy; } ;

/* Variables and functions */
 scalar_t__ PERF_CPU_MAP__CPUS ; 
 struct perf_cpu_map* cpu_map__from_entries (struct cpu_map_entries*) ; 
 struct perf_cpu_map* cpu_map__from_mask (struct perf_record_record_cpu_map*) ; 

struct perf_cpu_map *cpu_map__new_data(struct perf_record_cpu_map_data *data)
{
	if (data->type == PERF_CPU_MAP__CPUS)
		return cpu_map__from_entries((struct cpu_map_entries *)data->data);
	else
		return cpu_map__from_mask((struct perf_record_record_cpu_map *)data->data);
}