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
struct perf_env {TYPE_1__* cpu; } ;
struct cpu_map {int dummy; } ;
struct TYPE_2__ {int socket_id; int core_id; } ;

/* Variables and functions */
 int perf_env__get_cpu (struct perf_env*,struct cpu_map*,int) ; 

__attribute__((used)) static int perf_env__get_core(struct cpu_map *map, int idx, void *data)
{
	struct perf_env *env = data;
	int core = -1, cpu = perf_env__get_cpu(env, map, idx);

	if (cpu != -1) {
		int socket_id = env->cpu[cpu].socket_id;

		/*
		 * Encode socket in upper 16 bits
		 * core_id is relative to socket, and
		 * we need a global id. So we combine
		 * socket + core id.
		 */
		core = (socket_id << 16) | (env->cpu[cpu].core_id & 0xffff);
	}

	return core;
}