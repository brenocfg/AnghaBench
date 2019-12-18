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
struct rte_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTE_RING_QUEUE_FIXED ; 
 int __rte_ring_sp_do_enqueue (struct rte_ring*,void* const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
rte_ring_sp_enqueue_bulk(struct rte_ring *r, void * const *obj_table,
             unsigned n)
{
    return __rte_ring_sp_do_enqueue(r, obj_table, n, RTE_RING_QUEUE_FIXED);
}