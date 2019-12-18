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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkTimezoneIsUsedForCast (int,char*,char*) ; 
 int /*<<< orphan*/  time_timetz ; 

__attribute__((used)) static Datum
castTimeToTimeTz(Datum time, bool useTz)
{
	checkTimezoneIsUsedForCast(useTz, "time", "timetz");

	return DirectFunctionCall1(time_timetz, time);
}