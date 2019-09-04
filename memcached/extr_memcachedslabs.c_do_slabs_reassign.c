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
typedef  enum reassign_result_type { ____Placeholder_reassign_result_type } reassign_result_type ;
struct TYPE_4__ {int s_clsid; int d_clsid; } ;
struct TYPE_3__ {int slabs; } ;

/* Variables and functions */
 int REASSIGN_BADCLASS ; 
 int REASSIGN_NOSPARE ; 
 int REASSIGN_OK ; 
 int REASSIGN_RUNNING ; 
 int REASSIGN_SRC_DST_SAME ; 
 int SLAB_GLOBAL_PAGE_POOL ; 
 int power_largest ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ slab_rebal ; 
 int /*<<< orphan*/  slab_rebalance_cond ; 
 int slab_rebalance_signal ; 
 TYPE_1__* slabclass ; 
 int /*<<< orphan*/  slabs_lock ; 
 int slabs_reassign_pick_any (int) ; 

__attribute__((used)) static enum reassign_result_type do_slabs_reassign(int src, int dst) {
    bool nospare = false;
    if (slab_rebalance_signal != 0)
        return REASSIGN_RUNNING;

    if (src == dst)
        return REASSIGN_SRC_DST_SAME;

    /* Special indicator to choose ourselves. */
    if (src == -1) {
        src = slabs_reassign_pick_any(dst);
        /* TODO: If we end up back at -1, return a new error type */
    }

    if (src < SLAB_GLOBAL_PAGE_POOL || src > power_largest ||
        dst < SLAB_GLOBAL_PAGE_POOL || dst > power_largest)
        return REASSIGN_BADCLASS;

    pthread_mutex_lock(&slabs_lock);
    if (slabclass[src].slabs < 2)
        nospare = true;
    pthread_mutex_unlock(&slabs_lock);
    if (nospare)
        return REASSIGN_NOSPARE;

    slab_rebal.s_clsid = src;
    slab_rebal.d_clsid = dst;

    slab_rebalance_signal = 1;
    pthread_cond_signal(&slab_rebalance_cond);

    return REASSIGN_OK;
}