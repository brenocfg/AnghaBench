#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  Timestamp ;
typedef  int /*<<< orphan*/  Interval ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERVAL_TO_SEC (int /*<<< orphan*/ *) ; 
 scalar_t__ TIMESTAMP_NOT_FINITE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TimestampGetDatumFast (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_float8_infinity () ; 
 int /*<<< orphan*/  timestamp_mi ; 

__attribute__((used)) static float8
gbt_ts_dist(const void *a, const void *b, FmgrInfo *flinfo)
{
	const Timestamp *aa = (const Timestamp *) a;
	const Timestamp *bb = (const Timestamp *) b;
	Interval   *i;

	if (TIMESTAMP_NOT_FINITE(*aa) || TIMESTAMP_NOT_FINITE(*bb))
		return get_float8_infinity();

	i = DatumGetIntervalP(DirectFunctionCall2(timestamp_mi,
											  TimestampGetDatumFast(*aa),
											  TimestampGetDatumFast(*bb)));
	return (float8) Abs(INTERVAL_TO_SEC(i));
}