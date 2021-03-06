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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  storage_number ;
struct TYPE_5__ {TYPE_1__* rrdset; int /*<<< orphan*/ * values; } ;
struct TYPE_4__ {size_t current_entry; } ;
typedef  TYPE_2__ RRDDIM ;

/* Variables and functions */

__attribute__((used)) static void rrddim_collect_store_metric(RRDDIM *rd, usec_t point_in_time, storage_number number) {
    (void)point_in_time;

    rd->values[rd->rrdset->current_entry] = number;
}