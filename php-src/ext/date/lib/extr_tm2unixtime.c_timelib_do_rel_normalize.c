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
struct TYPE_5__ {int /*<<< orphan*/  m; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ timelib_time ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  m; int /*<<< orphan*/  invert; int /*<<< orphan*/  d; int /*<<< orphan*/  h; int /*<<< orphan*/  i; int /*<<< orphan*/  s; int /*<<< orphan*/  us; } ;
typedef  TYPE_2__ timelib_rel_time ;

/* Variables and functions */
 int /*<<< orphan*/  do_range_limit (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_range_limit_days_relative (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void timelib_do_rel_normalize(timelib_time *base, timelib_rel_time *rt)
{
	do_range_limit(0, 1000000, 1000000, &rt->us, &rt->s);
	do_range_limit(0, 60, 60, &rt->s, &rt->i);
	do_range_limit(0, 60, 60, &rt->i, &rt->h);
	do_range_limit(0, 24, 24, &rt->h, &rt->d);
	do_range_limit(0, 12, 12, &rt->m, &rt->y);

	do_range_limit_days_relative(&base->y, &base->m, &rt->y, &rt->m, &rt->d, rt->invert);
	do_range_limit(0, 12, 12, &rt->m, &rt->y);
}