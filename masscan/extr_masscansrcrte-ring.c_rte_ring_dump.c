#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; int tail; int head; scalar_t__ watermark; } ;
struct TYPE_3__ {int tail; int head; } ;
struct rte_ring {int flags; TYPE_2__ prod; TYPE_1__ cons; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int rte_ring_count (struct rte_ring const*) ; 
 int rte_ring_free_count (struct rte_ring const*) ; 

void
rte_ring_dump(const struct rte_ring *r)
{
#ifdef RTE_LIBRTE_RING_DEBUG
    struct rte_ring_debug_stats sum;
    unsigned lcore_id;
#endif

    printf("  flags=%x\n", r->flags);
    printf("  size=%u\n", r->prod.size);
    printf("  ct=%u\n", r->cons.tail);
    printf("  ch=%u\n", r->cons.head);
    printf("  pt=%u\n", r->prod.tail);
    printf("  ph=%u\n", r->prod.head);
    printf("  used=%u\n", rte_ring_count(r));
    printf("  avail=%u\n", rte_ring_free_count(r));
    if (r->prod.watermark == r->prod.size)
        printf("  watermark=0\n");
    else
        printf("  watermark=%u\n", r->prod.watermark);

    /* sum and dump statistics */
#ifdef RTE_LIBRTE_RING_DEBUG
    memset(&sum, 0, sizeof(sum));
    for (lcore_id = 0; lcore_id < RTE_MAX_LCORE; lcore_id++) {
        sum.enq_success_bulk += r->stats[lcore_id].enq_success_bulk;
        sum.enq_success_objs += r->stats[lcore_id].enq_success_objs;
        sum.enq_quota_bulk += r->stats[lcore_id].enq_quota_bulk;
        sum.enq_quota_objs += r->stats[lcore_id].enq_quota_objs;
        sum.enq_fail_bulk += r->stats[lcore_id].enq_fail_bulk;
        sum.enq_fail_objs += r->stats[lcore_id].enq_fail_objs;
        sum.deq_success_bulk += r->stats[lcore_id].deq_success_bulk;
        sum.deq_success_objs += r->stats[lcore_id].deq_success_objs;
        sum.deq_fail_bulk += r->stats[lcore_id].deq_fail_bulk;
        sum.deq_fail_objs += r->stats[lcore_id].deq_fail_objs;
    }
    printf("  size=%u\n", r->prod.size);
    printf("  enq_success_bulk=%"PRIu64"\n", sum.enq_success_bulk);
    printf("  enq_success_objs=%"PRIu64"\n", sum.enq_success_objs);
    printf("  enq_quota_bulk=%"PRIu64"\n", sum.enq_quota_bulk);
    printf("  enq_quota_objs=%"PRIu64"\n", sum.enq_quota_objs);
    printf("  enq_fail_bulk=%"PRIu64"\n", sum.enq_fail_bulk);
    printf("  enq_fail_objs=%"PRIu64"\n", sum.enq_fail_objs);
    printf("  deq_success_bulk=%"PRIu64"\n", sum.deq_success_bulk);
    printf("  deq_success_objs=%"PRIu64"\n", sum.deq_success_objs);
    printf("  deq_fail_bulk=%"PRIu64"\n", sum.deq_fail_bulk);
    printf("  deq_fail_objs=%"PRIu64"\n", sum.deq_fail_objs);
#else
    printf("  no statistics available\n");
#endif
}