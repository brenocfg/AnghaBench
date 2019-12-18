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
typedef  int /*<<< orphan*/  time64_t ;
struct tomoyo_time {scalar_t__ year; scalar_t__ month; int /*<<< orphan*/  day; int /*<<< orphan*/  hour; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;
struct tm {scalar_t__ tm_year; scalar_t__ tm_mon; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  time64_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 

void tomoyo_convert_time(time64_t time64, struct tomoyo_time *stamp)
{
	struct tm tm;

	time64_to_tm(time64, 0, &tm);
	stamp->sec = tm.tm_sec;
	stamp->min = tm.tm_min;
	stamp->hour = tm.tm_hour;
	stamp->day = tm.tm_mday;
	stamp->month = tm.tm_mon + 1;
	stamp->year = tm.tm_year + 1900;
}