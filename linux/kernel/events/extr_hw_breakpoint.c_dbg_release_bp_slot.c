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
struct TYPE_2__ {int /*<<< orphan*/  bp_type; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __release_bp_slot (struct perf_event*,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_bp_mutex ; 

int dbg_release_bp_slot(struct perf_event *bp)
{
	if (mutex_is_locked(&nr_bp_mutex))
		return -1;

	__release_bp_slot(bp, bp->attr.bp_type);

	return 0;
}