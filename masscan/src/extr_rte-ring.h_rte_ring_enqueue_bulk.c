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
struct TYPE_2__ {scalar_t__ sp_enqueue; } ;
struct rte_ring {TYPE_1__ prod; } ;

/* Variables and functions */
 int rte_ring_mp_enqueue_bulk (struct rte_ring*,void* const*,unsigned int) ; 
 int rte_ring_sp_enqueue_bulk (struct rte_ring*,void* const*,unsigned int) ; 

__attribute__((used)) static inline int
rte_ring_enqueue_bulk(struct rte_ring *r, void * const *obj_table,
              unsigned n)
{
    if (r->prod.sp_enqueue)
        return rte_ring_sp_enqueue_bulk(r, obj_table, n);
    else
        return rte_ring_mp_enqueue_bulk(r, obj_table, n);
}