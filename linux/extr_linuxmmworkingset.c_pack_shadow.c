#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long node_id; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 unsigned long MEM_CGROUP_ID_SHIFT ; 
 unsigned long NODES_SHIFT ; 
 unsigned long RADIX_TREE_EXCEPTIONAL_ENTRY ; 
 unsigned long RADIX_TREE_EXCEPTIONAL_SHIFT ; 
 unsigned long bucket_order ; 

__attribute__((used)) static void *pack_shadow(int memcgid, pg_data_t *pgdat, unsigned long eviction)
{
	eviction >>= bucket_order;
	eviction = (eviction << MEM_CGROUP_ID_SHIFT) | memcgid;
	eviction = (eviction << NODES_SHIFT) | pgdat->node_id;
	eviction = (eviction << RADIX_TREE_EXCEPTIONAL_SHIFT);

	return (void *)(eviction | RADIX_TREE_EXCEPTIONAL_ENTRY);
}