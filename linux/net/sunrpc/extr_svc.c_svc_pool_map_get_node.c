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
struct svc_pool_map {scalar_t__ mode; int* pool_to; scalar_t__ count; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 scalar_t__ SVC_POOL_PERCPU ; 
 scalar_t__ SVC_POOL_PERNODE ; 
 int cpu_to_node (int) ; 
 struct svc_pool_map svc_pool_map ; 

__attribute__((used)) static int svc_pool_map_get_node(unsigned int pidx)
{
	const struct svc_pool_map *m = &svc_pool_map;

	if (m->count) {
		if (m->mode == SVC_POOL_PERCPU)
			return cpu_to_node(m->pool_to[pidx]);
		if (m->mode == SVC_POOL_PERNODE)
			return m->pool_to[pidx];
	}
	return NUMA_NO_NODE;
}