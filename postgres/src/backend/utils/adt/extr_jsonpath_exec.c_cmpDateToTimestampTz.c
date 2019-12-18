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
typedef  int /*<<< orphan*/  DateADT ;

/* Variables and functions */
 int /*<<< orphan*/  checkTimezoneIsUsedForCast (int,char*,char*) ; 
 int cmpTimestampWithOverflow (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date2timestamptz_opt_overflow (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
cmpDateToTimestampTz(DateADT date1, TimestampTz tstz2, bool useTz)
{
	TimestampTz tstz1;
	int			overflow = 0;

	checkTimezoneIsUsedForCast(useTz, "date", "timestamptz");

	tstz1 = date2timestamptz_opt_overflow(date1, &overflow);

	return cmpTimestampWithOverflow(tstz1, overflow, tstz2);
}