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
typedef  int /*<<< orphan*/  pg_data_t ;

/* Variables and functions */
 unsigned long MEM_CGROUP_ID_SHIFT ; 
 unsigned long NODES_SHIFT ; 
 int /*<<< orphan*/ * NODE_DATA (int) ; 
 unsigned long bucket_order ; 
 unsigned long xa_to_value (void*) ; 

__attribute__((used)) static void unpack_shadow(void *shadow, int *memcgidp, pg_data_t **pgdat,
			  unsigned long *evictionp, bool *workingsetp)
{
	unsigned long entry = xa_to_value(shadow);
	int memcgid, nid;
	bool workingset;

	workingset = entry & 1;
	entry >>= 1;
	nid = entry & ((1UL << NODES_SHIFT) - 1);
	entry >>= NODES_SHIFT;
	memcgid = entry & ((1UL << MEM_CGROUP_ID_SHIFT) - 1);
	entry >>= MEM_CGROUP_ID_SHIFT;

	*memcgidp = memcgid;
	*pgdat = NODE_DATA(nid);
	*evictionp = entry << bucket_order;
	*workingsetp = workingset;
}