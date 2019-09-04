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
struct mem_cgroup {int dummy; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int init_memcg_params(struct kmem_cache *s,
		struct mem_cgroup *memcg, struct kmem_cache *root_cache)
{
	return 0;
}