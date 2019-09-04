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
struct grouping_des {double level; double trend; scalar_t__ count; } ;
struct TYPE_4__ {scalar_t__ grouping_data; } ;
struct TYPE_5__ {TYPE_1__ internal; } ;
typedef  TYPE_2__ RRDR ;

/* Variables and functions */

void grouping_reset_des(RRDR *r) {
    struct grouping_des *g = (struct grouping_des *)r->internal.grouping_data;
    g->level = 0.0;
    g->trend = 0.0;
    g->count = 0;

    // fprintf(stderr, "\nDES: ");

}