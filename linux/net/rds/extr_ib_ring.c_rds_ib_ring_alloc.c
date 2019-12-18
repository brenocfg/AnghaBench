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
typedef  int u32 ;
struct rds_ib_work_ring {int w_nr; int w_alloc_ptr; int w_alloc_ctr; } ;

/* Variables and functions */
 int __rds_ib_ring_used (struct rds_ib_work_ring*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_ib_work_ring*,int,int,int) ; 

u32 rds_ib_ring_alloc(struct rds_ib_work_ring *ring, u32 val, u32 *pos)
{
	u32 ret = 0, avail;

	avail = ring->w_nr - __rds_ib_ring_used(ring);

	rdsdebug("ring %p val %u next %u free %u\n", ring, val,
		 ring->w_alloc_ptr, avail);

	if (val && avail) {
		ret = min(val, avail);
		*pos = ring->w_alloc_ptr;

		ring->w_alloc_ptr = (ring->w_alloc_ptr + ret) % ring->w_nr;
		ring->w_alloc_ctr += ret;
	}

	return ret;
}