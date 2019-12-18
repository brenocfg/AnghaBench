#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int total_pages; unsigned int chunks_per_page; } ;
typedef  TYPE_2__ slab_stats_automove ;
struct TYPE_7__ {scalar_t__ last_memcheck_run; unsigned int free_ratio; unsigned int* free_mem; TYPE_2__* sam_after; TYPE_1__* settings; scalar_t__ pool_filled_once; } ;
typedef  TYPE_3__ slab_automove ;
struct TYPE_5__ {unsigned int* ext_free_memchunks; } ;

/* Variables and functions */
 int MAX_NUMBER_OF_SLAB_CLASSES ; 
 scalar_t__ MEMCHECK_PERIOD ; 
 unsigned int MIN_PAGES_FREE ; 
 scalar_t__ current_time ; 

__attribute__((used)) static void memcheck(slab_automove *a) {
    unsigned int total_pages = 0;
    if (current_time < a->last_memcheck_run + MEMCHECK_PERIOD)
        return;
    a->last_memcheck_run = current_time;
    for (int n = 1; n < MAX_NUMBER_OF_SLAB_CLASSES; n++) {
        slab_stats_automove *sam = &a->sam_after[n];
        total_pages += sam->total_pages;
        unsigned int hold_free = (sam->total_pages * sam->chunks_per_page)
            * a->free_ratio;
        if (sam->chunks_per_page * MIN_PAGES_FREE > hold_free)
            hold_free = sam->chunks_per_page * MIN_PAGES_FREE;
        a->free_mem[n] = hold_free;
        if (a->settings->ext_free_memchunks[n] != hold_free && a->pool_filled_once) {
            a->settings->ext_free_memchunks[n] = hold_free;
        }
    }
    // remember to add what remains in global pool.
    total_pages += a->sam_after[0].total_pages;
    a->free_mem[0] = total_pages * a->free_ratio;
}