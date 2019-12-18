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
struct perf_cpu_map {int dummy; } ;
struct TYPE_2__ {int socket_id; int die_id; int core_id; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int perf_env__get_cpu (struct perf_env*,struct perf_cpu_map*,int) ; 

__attribute__((used)) static int perf_env__get_core(struct perf_cpu_map *map, int idx, void *data)
{
	struct perf_env *env = data;
	int core = -1, cpu = perf_env__get_cpu(env, map, idx);

	if (cpu != -1) {
		/*
		 * Encode socket in bit range 31:24
		 * encode die id in bit range 23:16
		 * core_id is relative to socket and die,
		 * we need a global id. So we combine
		 * socket + die id + core id
		 */
		if (WARN_ONCE(env->cpu[cpu].socket_id >> 8, "The socket id number is too big.\n"))
			return -1;

		if (WARN_ONCE(env->cpu[cpu].die_id >> 8, "The die id number is too big.\n"))
			return -1;

		if (WARN_ONCE(env->cpu[cpu].core_id >> 16, "The core id number is too big.\n"))
			return -1;

		core = (env->cpu[cpu].socket_id << 24) |
		       (env->cpu[cpu].die_id << 16) |
		       (env->cpu[cpu].core_id & 0xffff);
	}

	return core;
}