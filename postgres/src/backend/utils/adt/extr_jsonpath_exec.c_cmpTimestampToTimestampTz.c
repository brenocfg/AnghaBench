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
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  Timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  checkTimezoneIsUsedForCast (int,char*,char*) ; 
 int cmpTimestampWithOverflow (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamp2timestamptz_opt_overflow (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
cmpTimestampToTimestampTz(Timestamp ts1, TimestampTz tstz2, bool useTz)
{
	TimestampTz tstz1;
	int			overflow = 0;

	checkTimezoneIsUsedForCast(useTz, "timestamp", "timestamptz");

	tstz1 = timestamp2timestamptz_opt_overflow(ts1, &overflow);

	return cmpTimestampWithOverflow(tstz1, overflow, tstz2);
}