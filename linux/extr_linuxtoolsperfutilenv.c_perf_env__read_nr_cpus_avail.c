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
struct perf_env {scalar_t__ nr_cpus_avail; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ cpu__max_present_cpu () ; 

__attribute__((used)) static int perf_env__read_nr_cpus_avail(struct perf_env *env)
{
	if (env->nr_cpus_avail == 0)
		env->nr_cpus_avail = cpu__max_present_cpu();

	return env->nr_cpus_avail ? 0 : -ENOENT;
}