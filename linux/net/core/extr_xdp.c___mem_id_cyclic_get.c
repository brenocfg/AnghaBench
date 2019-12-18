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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  MEM_ID_MAX ; 
 int MEM_ID_MIN ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mem_id_next ; 
 int /*<<< orphan*/  mem_id_pool ; 

__attribute__((used)) static int __mem_id_cyclic_get(gfp_t gfp)
{
	int retries = 1;
	int id;

again:
	id = ida_simple_get(&mem_id_pool, mem_id_next, MEM_ID_MAX, gfp);
	if (id < 0) {
		if (id == -ENOSPC) {
			/* Cyclic allocator, reset next id */
			if (retries--) {
				mem_id_next = MEM_ID_MIN;
				goto again;
			}
		}
		return id; /* errno */
	}
	mem_id_next = id + 1;

	return id;
}