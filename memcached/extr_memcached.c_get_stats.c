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
struct TYPE_4__ {scalar_t__ total_items; } ;
struct TYPE_3__ {scalar_t__ curr_items; scalar_t__ curr_bytes; } ;
typedef  int /*<<< orphan*/ * ADD_STAT ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_STAT (char*,char*,unsigned long long) ; 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 unsigned long long global_page_pool_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  item_stats (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  item_stats_sizes (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  item_stats_sizes_disable (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  item_stats_sizes_enable (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  item_stats_totals (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ nz_strcmp (int,char const*,char*) ; 
 int /*<<< orphan*/  slabs_stats (int /*<<< orphan*/ *,void*) ; 
 TYPE_2__ stats ; 
 TYPE_1__ stats_state ; 

__attribute__((used)) static bool get_stats(const char *stat_type, int nkey, ADD_STAT add_stats, void *c) {
    bool ret = true;

    if (add_stats != NULL) {
        if (!stat_type) {
            /* prepare general statistics for the engine */
            STATS_LOCK();
            APPEND_STAT("bytes", "%llu", (unsigned long long)stats_state.curr_bytes);
            APPEND_STAT("curr_items", "%llu", (unsigned long long)stats_state.curr_items);
            APPEND_STAT("total_items", "%llu", (unsigned long long)stats.total_items);
            STATS_UNLOCK();
            APPEND_STAT("slab_global_page_pool", "%u", global_page_pool_size(NULL));
            item_stats_totals(add_stats, c);
        } else if (nz_strcmp(nkey, stat_type, "items") == 0) {
            item_stats(add_stats, c);
        } else if (nz_strcmp(nkey, stat_type, "slabs") == 0) {
            slabs_stats(add_stats, c);
        } else if (nz_strcmp(nkey, stat_type, "sizes") == 0) {
            item_stats_sizes(add_stats, c);
        } else if (nz_strcmp(nkey, stat_type, "sizes_enable") == 0) {
            item_stats_sizes_enable(add_stats, c);
        } else if (nz_strcmp(nkey, stat_type, "sizes_disable") == 0) {
            item_stats_sizes_disable(add_stats, c);
        } else {
            ret = false;
        }
    } else {
        ret = false;
    }

    return ret;
}