#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grouping_incremental_sum {scalar_t__ count; scalar_t__ last; scalar_t__ first; } ;
struct TYPE_4__ {scalar_t__ grouping_data; } ;
struct TYPE_5__ {TYPE_1__ internal; } ;
typedef  TYPE_2__ RRDR ;

/* Variables and functions */

void grouping_reset_incremental_sum(RRDR *r) {
    struct grouping_incremental_sum *g = (struct grouping_incremental_sum *)r->internal.grouping_data;
    g->first = 0;
    g->last = 0;
    g->count = 0;
}