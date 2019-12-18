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
struct grouping_average {int /*<<< orphan*/  count; int /*<<< orphan*/  sum; } ;
typedef  scalar_t__ calculated_number ;
struct TYPE_4__ {scalar_t__ grouping_data; } ;
struct TYPE_5__ {TYPE_1__ internal; } ;
typedef  TYPE_2__ RRDR ;

/* Variables and functions */
 int /*<<< orphan*/  isnan (scalar_t__) ; 

void grouping_add_average(RRDR *r, calculated_number value) {
    if(!isnan(value)) {
        struct grouping_average *g = (struct grouping_average *)r->internal.grouping_data;
        g->sum += value;
        g->count++;
    }
}