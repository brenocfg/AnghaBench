#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ truncate; } ;
typedef  TYPE_1__ VacuumParams ;
struct TYPE_6__ {int rel_pages; int nonempty_pages; } ;
typedef  TYPE_2__ LVRelStats ;
typedef  int BlockNumber ;

/* Variables and functions */
 int REL_TRUNCATE_FRACTION ; 
 int REL_TRUNCATE_MINIMUM ; 
 scalar_t__ VACOPT_TERNARY_DISABLED ; 
 scalar_t__ old_snapshot_threshold ; 

__attribute__((used)) static bool
should_attempt_truncation(VacuumParams *params, LVRelStats *vacrelstats)
{
	BlockNumber possibly_freeable;

	if (params->truncate == VACOPT_TERNARY_DISABLED)
		return false;

	possibly_freeable = vacrelstats->rel_pages - vacrelstats->nonempty_pages;
	if (possibly_freeable > 0 &&
		(possibly_freeable >= REL_TRUNCATE_MINIMUM ||
		 possibly_freeable >= vacrelstats->rel_pages / REL_TRUNCATE_FRACTION) &&
		old_snapshot_threshold < 0)
		return true;
	else
		return false;
}