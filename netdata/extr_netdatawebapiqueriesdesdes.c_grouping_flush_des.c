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
struct grouping_des {double level; int /*<<< orphan*/  count; } ;
typedef  double calculated_number ;
struct TYPE_4__ {scalar_t__ grouping_data; } ;
struct TYPE_5__ {TYPE_1__ internal; } ;
typedef  int /*<<< orphan*/  RRDR_VALUE_FLAGS ;
typedef  TYPE_2__ RRDR ;

/* Variables and functions */
 int /*<<< orphan*/  RRDR_VALUE_EMPTY ; 
 int /*<<< orphan*/  calculated_number_isnumber (double) ; 
 scalar_t__ unlikely (int) ; 

calculated_number grouping_flush_des(RRDR *r, RRDR_VALUE_FLAGS *rrdr_value_options_ptr) {
    struct grouping_des *g = (struct grouping_des *)r->internal.grouping_data;

    if(unlikely(!g->count || !calculated_number_isnumber(g->level))) {
        *rrdr_value_options_ptr |= RRDR_VALUE_EMPTY;
        return 0.0;
    }

    //fprintf(stderr, " RESULT for %zu values = " CALCULATED_NUMBER_FORMAT " \n", g->count, g->level);

    return g->level;
}