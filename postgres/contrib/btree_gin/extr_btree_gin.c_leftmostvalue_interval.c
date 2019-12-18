#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ month; scalar_t__ day; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ Interval ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NOBEGIN ; 
 int /*<<< orphan*/  IntervalPGetDatum (TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 

__attribute__((used)) static Datum
leftmostvalue_interval(void)
{
	Interval   *v = palloc(sizeof(Interval));

	v->time = DT_NOBEGIN;
	v->day = 0;
	v->month = 0;
	return IntervalPGetDatum(v);
}