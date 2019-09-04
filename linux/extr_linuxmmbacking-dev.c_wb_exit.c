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
struct bdi_writeback {TYPE_1__* bdi; int /*<<< orphan*/  congested; int /*<<< orphan*/  completions; int /*<<< orphan*/ * stat; int /*<<< orphan*/  dwork; } ;
struct TYPE_2__ {struct bdi_writeback wb; } ;

/* Variables and functions */
 int NR_WB_STAT_ITEMS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdi_put (TYPE_1__*) ; 
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprop_local_destroy_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_congested_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wb_exit(struct bdi_writeback *wb)
{
	int i;

	WARN_ON(delayed_work_pending(&wb->dwork));

	for (i = 0; i < NR_WB_STAT_ITEMS; i++)
		percpu_counter_destroy(&wb->stat[i]);

	fprop_local_destroy_percpu(&wb->completions);
	wb_congested_put(wb->congested);
	if (wb != &wb->bdi->wb)
		bdi_put(wb->bdi);
}