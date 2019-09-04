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
struct svc_serv {unsigned int sv_nrpools; struct svc_pool* sv_pools; } ;
struct svc_pool_map {int mode; unsigned int* to_pool; } ;
struct svc_pool {int dummy; } ;

/* Variables and functions */
#define  SVC_POOL_PERCPU 129 
#define  SVC_POOL_PERNODE 128 
 size_t cpu_to_node (int) ; 
 struct svc_pool_map svc_pool_map ; 
 scalar_t__ svc_serv_is_pooled (struct svc_serv*) ; 

struct svc_pool *
svc_pool_for_cpu(struct svc_serv *serv, int cpu)
{
	struct svc_pool_map *m = &svc_pool_map;
	unsigned int pidx = 0;

	/*
	 * An uninitialised map happens in a pure client when
	 * lockd is brought up, so silently treat it the
	 * same as SVC_POOL_GLOBAL.
	 */
	if (svc_serv_is_pooled(serv)) {
		switch (m->mode) {
		case SVC_POOL_PERCPU:
			pidx = m->to_pool[cpu];
			break;
		case SVC_POOL_PERNODE:
			pidx = m->to_pool[cpu_to_node(cpu)];
			break;
		}
	}
	return &serv->sv_pools[pidx % serv->sv_nrpools];
}