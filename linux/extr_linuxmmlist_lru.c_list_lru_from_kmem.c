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
struct list_lru_one {int dummy; } ;
struct list_lru_node {struct list_lru_one lru; } ;

/* Variables and functions */

__attribute__((used)) static inline struct list_lru_one *
list_lru_from_kmem(struct list_lru_node *nlru, void *ptr,
		   struct mem_cgroup **memcg_ptr)
{
	if (memcg_ptr)
		*memcg_ptr = NULL;
	return &nlru->lru;
}