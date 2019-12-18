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
typedef  int /*<<< orphan*/  DateADT ;

/* Variables and functions */
 int cmpTimestampWithOverflow (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date2timestamp_opt_overflow (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
cmpDateToTimestamp(DateADT date1, Timestamp ts2, bool useTz)
{
	TimestampTz ts1;
	int			overflow = 0;

	ts1 = date2timestamp_opt_overflow(date1, &overflow);

	return cmpTimestampWithOverflow(ts1, overflow, ts2);
}