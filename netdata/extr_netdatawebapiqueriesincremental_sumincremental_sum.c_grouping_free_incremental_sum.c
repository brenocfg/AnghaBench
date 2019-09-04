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
struct TYPE_4__ {int /*<<< orphan*/ * grouping_data; } ;
struct TYPE_5__ {TYPE_1__ internal; } ;
typedef  TYPE_2__ RRDR ;

/* Variables and functions */
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 

void grouping_free_incremental_sum(RRDR *r) {
    freez(r->internal.grouping_data);
    r->internal.grouping_data = NULL;
}