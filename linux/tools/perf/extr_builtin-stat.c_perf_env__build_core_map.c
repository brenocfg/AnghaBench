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
struct perf_env {int dummy; } ;
struct perf_cpu_map {int dummy; } ;

/* Variables and functions */
 int cpu_map__build_map (struct perf_cpu_map*,struct perf_cpu_map**,int /*<<< orphan*/ ,struct perf_env*) ; 
 int /*<<< orphan*/  perf_env__get_core ; 

__attribute__((used)) static int perf_env__build_core_map(struct perf_env *env, struct perf_cpu_map *cpus,
				    struct perf_cpu_map **corep)
{
	return cpu_map__build_map(cpus, corep, perf_env__get_core, env);
}