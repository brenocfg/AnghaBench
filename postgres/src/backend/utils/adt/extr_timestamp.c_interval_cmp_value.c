#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_3__ {int time; int month; scalar_t__ day; } ;
typedef  TYPE_1__ Interval ;
typedef  int /*<<< orphan*/  INT128 ;

/* Variables and functions */
 int INT64CONST (int) ; 
 int USECS_PER_DAY ; 
 int /*<<< orphan*/  int128_add_int64_mul_int64 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  int64_to_int128 (int) ; 

__attribute__((used)) static inline INT128
interval_cmp_value(const Interval *interval)
{
	INT128		span;
	int64		dayfraction;
	int64		days;

	/*
	 * Separate time field into days and dayfraction, then add the month and
	 * day fields to the days part.  We cannot overflow int64 days here.
	 */
	dayfraction = interval->time % USECS_PER_DAY;
	days = interval->time / USECS_PER_DAY;
	days += interval->month * INT64CONST(30);
	days += interval->day;

	/* Widen dayfraction to 128 bits */
	span = int64_to_int128(dayfraction);

	/* Scale up days to microseconds, forming a 128-bit product */
	int128_add_int64_mul_int64(&span, days, USECS_PER_DAY);

	return span;
}