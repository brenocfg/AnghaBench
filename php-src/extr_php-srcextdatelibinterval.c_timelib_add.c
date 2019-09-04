#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int y; int m; int d; int h; int i; int s; int us; } ;
struct TYPE_14__ {int have_relative; int dst; scalar_t__ z; int /*<<< orphan*/  sse; scalar_t__ sse_uptodate; TYPE_10__ relative; } ;
typedef  TYPE_1__ timelib_time ;
struct TYPE_15__ {int y; int m; int d; int h; int i; int s; int us; scalar_t__ invert; scalar_t__ have_special_relative; scalar_t__ have_weekday_relative; } ;
typedef  TYPE_2__ timelib_rel_time ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_10__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* timelib_time_clone (TYPE_1__*) ; 
 int /*<<< orphan*/  timelib_update_from_sse (TYPE_1__*) ; 
 int /*<<< orphan*/  timelib_update_ts (TYPE_1__*,int /*<<< orphan*/ *) ; 

timelib_time *timelib_add(timelib_time *old_time, timelib_rel_time *interval)
{
	int bias = 1;
	timelib_time *t = timelib_time_clone(old_time);

	if (interval->have_weekday_relative || interval->have_special_relative) {
		memcpy(&t->relative, interval, sizeof(timelib_rel_time));
	} else {
		if (interval->invert) {
			bias = -1;
		}
		memset(&t->relative, 0, sizeof(timelib_rel_time));
		t->relative.y = interval->y * bias;
		t->relative.m = interval->m * bias;
		t->relative.d = interval->d * bias;
		t->relative.h = interval->h * bias;
		t->relative.i = interval->i * bias;
		t->relative.s = interval->s * bias;
		t->relative.us = interval->us * bias;
	}
	t->have_relative = 1;
	t->sse_uptodate = 0;

	timelib_update_ts(t, NULL);

//	printf("%lld %lld %d\n", old_time->dst, t->dst, (t->sse - old_time->sse));
	/* Adjust for backwards DST changeover */
	if (old_time->dst == 1 && t->dst == 0 && !interval->y && !interval->m && !interval->d) {
		t->sse -= old_time->z;
		t->sse += t->z;
	}

	timelib_update_from_sse(t);
	t->have_relative = 0;

	return t;
}