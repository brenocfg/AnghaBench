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
struct TYPE_3__ {int /*<<< orphan*/  qidlestart; int /*<<< orphan*/  qavg; } ;
struct gred_sched_data {TYPE_1__ vars; } ;
struct TYPE_4__ {int /*<<< orphan*/  qidlestart; int /*<<< orphan*/  qavg; } ;
struct gred_sched {TYPE_2__ wred_set; } ;

/* Variables and functions */

__attribute__((used)) static inline void gred_load_wred_set(const struct gred_sched *table,
				      struct gred_sched_data *q)
{
	q->vars.qavg = table->wred_set.qavg;
	q->vars.qidlestart = table->wred_set.qidlestart;
}