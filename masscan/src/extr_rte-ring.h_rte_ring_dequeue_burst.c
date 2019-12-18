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
struct TYPE_2__ {scalar_t__ sc_dequeue; } ;
struct rte_ring {TYPE_1__ cons; } ;

/* Variables and functions */
 int rte_ring_mc_dequeue_burst (struct rte_ring*,void**,unsigned int) ; 
 int rte_ring_sc_dequeue_burst (struct rte_ring*,void**,unsigned int) ; 

__attribute__((used)) static inline int
rte_ring_dequeue_burst(struct rte_ring *r, void **obj_table, unsigned n)
{
    if (r->cons.sc_dequeue)
        return rte_ring_sc_dequeue_burst(r, obj_table, n);
    else
        return rte_ring_mc_dequeue_burst(r, obj_table, n);
}