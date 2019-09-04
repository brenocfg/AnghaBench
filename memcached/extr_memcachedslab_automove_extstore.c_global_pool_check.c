#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct window_global {int pool_low; int pool_high; } ;
struct TYPE_3__ {int* free_mem; size_t window_cur; size_t window_size; int pool_filled_once; struct window_global* window_global; } ;
typedef  TYPE_1__ slab_automove ;

/* Variables and functions */
 unsigned int global_page_pool_size (int*) ; 
 int /*<<< orphan*/  memset (struct window_global*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void global_pool_check(slab_automove *a) {
    bool mem_limit_reached;
    uint32_t free = a->free_mem[0];
    struct window_global *wg = &a->window_global[a->window_cur % a->window_size];
    unsigned int count = global_page_pool_size(&mem_limit_reached);
    memset(wg, 0, sizeof(struct window_global));
    if (!mem_limit_reached)
        return;
    if (count < free / 2) {
        wg->pool_low = 1;
        a->pool_filled_once = true;
    } else if (count > free) {
        wg->pool_high = 1;
    } else {
        a->pool_filled_once = true;
    }
}