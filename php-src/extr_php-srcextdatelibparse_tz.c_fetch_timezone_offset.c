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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ttinfo ;
struct TYPE_4__ {size_t timecnt; int typecnt; } ;
struct TYPE_5__ {scalar_t__* trans; size_t* trans_idx; TYPE_1__ bit64; int /*<<< orphan*/ * type; } ;
typedef  TYPE_2__ timelib_tzinfo ;
typedef  scalar_t__ timelib_sll ;

/* Variables and functions */

__attribute__((used)) static ttinfo* fetch_timezone_offset(timelib_tzinfo *tz, timelib_sll ts, timelib_sll *transition_time)
{
	uint32_t i;

	/* If there is no transition time, we pick the first one, if that doesn't
	 * exist we return NULL */
	if (!tz->bit64.timecnt || !tz->trans) {
		*transition_time = 0;
		if (tz->bit64.typecnt == 1) {
			return &(tz->type[0]);
		}
		return NULL;
	}

	/* If the TS is lower than the first transition time, then we scan over
	 * all the transition times to find the first non-DST one, or the first
	 * one in case there are only DST entries. Not sure which smartass came up
	 * with this idea in the first though :) */
	if (ts < tz->trans[0]) {
		return &(tz->type[0]);
	}

	/* In all other cases we loop through the available transition times to find
	 * the correct entry */
	for (i = 0; i < tz->bit64.timecnt; i++) {
		if (ts < tz->trans[i]) {
			*transition_time = tz->trans[i - 1];
			return &(tz->type[tz->trans_idx[i - 1]]);
		}
	}
	*transition_time = tz->trans[tz->bit64.timecnt - 1];
	return &(tz->type[tz->trans_idx[tz->bit64.timecnt - 1]]);
}