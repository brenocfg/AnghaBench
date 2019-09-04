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
struct TYPE_4__ {int sc_dequeue; unsigned int size; unsigned int mask; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_3__ {unsigned int watermark; int sp_enqueue; unsigned int size; unsigned int mask; scalar_t__ tail; scalar_t__ head; } ;
struct rte_ring {unsigned int flags; TYPE_2__ cons; TYPE_1__ prod; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  POWEROF2 (unsigned int) ; 
 unsigned int RING_F_SC_DEQ ; 
 unsigned int RING_F_SP_ENQ ; 
 unsigned int RTE_RING_SZ_MASK ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct rte_ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rte_errno ; 
 int /*<<< orphan*/  stderr ; 

struct rte_ring *
rte_ring_create(unsigned count, unsigned flags)
{
    struct rte_ring *r;
    size_t ring_size;

#if 0
    /* compilation-time checks */
    RTE_BUILD_BUG_ON((sizeof(struct rte_ring) &
              CACHE_LINE_MASK) != 0);
    RTE_BUILD_BUG_ON((offsetof(struct rte_ring, cons) &
              CACHE_LINE_MASK) != 0);
    RTE_BUILD_BUG_ON((offsetof(struct rte_ring, prod) &
              CACHE_LINE_MASK) != 0);
#ifdef RTE_LIBRTE_RING_DEBUG
    RTE_BUILD_BUG_ON((sizeof(struct rte_ring_debug_stats) &
              CACHE_LINE_MASK) != 0);
    RTE_BUILD_BUG_ON((offsetof(struct rte_ring, stats) &
              CACHE_LINE_MASK) != 0);
#endif
#endif

    /* count must be a power of 2 */
    if ((!POWEROF2(count)) || (count > RTE_RING_SZ_MASK )) {
        rte_errno = EINVAL;
        fprintf(stderr, "Requested size is invalid, must be power of 2, and "
                "do not exceed the size limit %u\n", RTE_RING_SZ_MASK);
        return NULL;
    }

    ring_size = count * sizeof(void *) + sizeof(struct rte_ring);

    r = (struct rte_ring*)malloc(ring_size);
    if (r == NULL)
        abort();

    /* init the ring structure */
    memset(r, 0, sizeof(*r));

    r->flags = flags;
    r->prod.watermark = count;
    r->prod.sp_enqueue = !!(flags & RING_F_SP_ENQ);
    r->cons.sc_dequeue = !!(flags & RING_F_SC_DEQ);
    r->prod.size = r->cons.size = count;
    r->prod.mask = r->cons.mask = count-1;
    r->prod.head = r->cons.head = 0;
    r->prod.tail = r->cons.tail = 0;

    return r;
}