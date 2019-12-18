#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 TYPE_1__* DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntervalPGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  interval_lt ; 
 int /*<<< orphan*/  interval_um ; 

Interval *
abs_interval(Interval *a)
{
	static Interval zero = {0, 0, 0};

	if (DatumGetBool(DirectFunctionCall2(interval_lt,
										 IntervalPGetDatum(a),
										 IntervalPGetDatum(&zero))))
		a = DatumGetIntervalP(DirectFunctionCall1(interval_um,
												  IntervalPGetDatum(a)));

	return a;
}