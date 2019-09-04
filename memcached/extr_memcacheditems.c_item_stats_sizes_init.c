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
struct TYPE_2__ {int item_size_max; scalar_t__ use_cas; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  get_cas_id () ; 
 TYPE_1__ settings ; 
 int stats_sizes_buckets ; 
 int /*<<< orphan*/  stats_sizes_cas_min ; 
 int /*<<< orphan*/ * stats_sizes_hist ; 

void item_stats_sizes_init(void) {
    if (stats_sizes_hist != NULL)
        return;
    stats_sizes_buckets = settings.item_size_max / 32 + 1;
    stats_sizes_hist = calloc(stats_sizes_buckets, sizeof(int));
    stats_sizes_cas_min = (settings.use_cas) ? get_cas_id() : 0;
}