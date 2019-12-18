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
struct Test {int /*<<< orphan*/  producer_done; int /*<<< orphan*/  producer_started; struct rte_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  pixie_locked_add_u32 (int /*<<< orphan*/ *,int) ; 
 int rte_ring_sp_enqueue (struct rte_ring*,void*) ; 

__attribute__((used)) static void
test_producer_thread(void *v)
{
    struct Test *test = (struct Test *)v;
    unsigned i = 1000;
    struct rte_ring *ring = test->ring;

    pixie_locked_add_u32(&test->producer_started, 1);
    while (i) {
        int err;
        for (;;) {
            err = rte_ring_sp_enqueue(ring, (void*)(size_t)i);
            if (err == 0)
                break;
        }
        i--;
    }
    pixie_locked_add_u32(&test->producer_done, 1);
}