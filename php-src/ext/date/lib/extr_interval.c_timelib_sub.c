#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ us; scalar_t__ s; scalar_t__ i; scalar_t__ h; scalar_t__ d; scalar_t__ m; scalar_t__ y; } ;
struct TYPE_12__ {int have_relative; int dst; scalar_t__ z; int /*<<< orphan*/  sse; scalar_t__ sse_uptodate; TYPE_10__ relative; } ;
typedef  TYPE_1__ timelib_time ;
struct TYPE_13__ {int y; int m; int d; int h; int i; int s; int us; scalar_t__ invert; } ;
typedef  TYPE_2__ timelib_rel_time ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* timelib_time_clone (TYPE_1__*) ; 
 int /*<<< orphan*/  timelib_update_from_sse (TYPE_1__*) ; 
 int /*<<< orphan*/  timelib_update_ts (TYPE_1__*,int /*<<< orphan*/ *) ; 

timelib_time *timelib_sub(timelib_time *old_time, timelib_rel_time *interval)
{
	int bias = 1;
	timelib_time *t = timelib_time_clone(old_time);

	if (interval->invert) {
		bias = -1;
	}

	memset(&t->relative, 0, sizeof(timelib_rel_time));
	t->relative.y = 0 - (interval->y * bias);
	t->relative.m = 0 - (interval->m * bias);
	t->relative.d = 0 - (interval->d * bias);
	t->relative.h = 0 - (interval->h * bias);
	t->relative.i = 0 - (interval->i * bias);
	t->relative.s = 0 - (interval->s * bias);
	t->relative.us = 0 - (interval->us * bias);
	t->have_relative = 1;
	t->sse_uptodate = 0;

	timelib_update_ts(t, NULL);

	/* Adjust for backwards DST changeover */
	if (old_time->dst == 1 && t->dst == 0 && !interval->y && !interval->m && !interval->d) {
		t->sse -= old_time->z;
		t->sse += t->z;
	}
	/* Adjust for forwards DST changeover */
	if (old_time->dst == 0 && t->dst == 1 && !interval->y && !interval->m && !interval->d ) {
		t->sse -= old_time->z;
		t->sse += t->z;
	}

	timelib_update_from_sse(t);

	t->have_relative = 0;

	return t;
}