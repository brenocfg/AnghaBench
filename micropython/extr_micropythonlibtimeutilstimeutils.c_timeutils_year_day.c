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
typedef  int mp_uint_t ;

/* Variables and functions */
 int* days_since_jan1 ; 
 scalar_t__ timeutils_is_leap_year (int) ; 

mp_uint_t timeutils_year_day(mp_uint_t year, mp_uint_t month, mp_uint_t date) {
    mp_uint_t yday = days_since_jan1[month - 1] + date;
    if (month >= 3 && timeutils_is_leap_year(year)) {
        yday += 1;
    }
    return yday;
}