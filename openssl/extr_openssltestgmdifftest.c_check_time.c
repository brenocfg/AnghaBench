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
typedef  scalar_t__ time_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_gmtime (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  OPENSSL_gmtime_adj (struct tm*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  OPENSSL_gmtime_diff (int*,int*,struct tm*,struct tm*) ; 
 long SECS_PER_DAY ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_long_eq (long,long) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

__attribute__((used)) static int check_time(long offset)
{
    struct tm tm1, tm2, o1;
    int off_day, off_sec;
    long toffset;
    time_t t1, t2;

    time(&t1);

    t2 = t1 + offset;
    OPENSSL_gmtime(&t2, &tm2);
    OPENSSL_gmtime(&t1, &tm1);
    o1 = tm1;
    OPENSSL_gmtime_adj(&tm1, 0, offset);
    if (!TEST_int_eq(tm1.tm_year, tm2.tm_year)
        || !TEST_int_eq(tm1.tm_mon, tm2.tm_mon)
        || !TEST_int_eq(tm1.tm_mday, tm2.tm_mday)
        || !TEST_int_eq(tm1.tm_hour, tm2.tm_hour)
        || !TEST_int_eq(tm1.tm_min, tm2.tm_min)
        || !TEST_int_eq(tm1.tm_sec, tm2.tm_sec)
        || !TEST_true(OPENSSL_gmtime_diff(&off_day, &off_sec, &o1, &tm1)))
        return 0;
    toffset = (long)off_day * SECS_PER_DAY + off_sec;
    if (!TEST_long_eq(offset, toffset))
        return 0;
    return 1;
}