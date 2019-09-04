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
typedef  int npy_int64 ;
typedef  scalar_t__ npy_datetime ;
typedef  scalar_t__ npy_bool ;
typedef  int /*<<< orphan*/  NPY_BUSDAY_ROLL ;

/* Variables and functions */
 scalar_t__ NPY_DATETIME_NAT ; 
 scalar_t__ apply_business_day_roll (scalar_t__,scalar_t__*,int*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__* find_earliest_holiday_after (scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__* find_earliest_holiday_on_or_after (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  is_holiday (scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
apply_business_day_offset(npy_datetime date, npy_int64 offset,
                    npy_datetime *out,
                    NPY_BUSDAY_ROLL roll,
                    npy_bool *weekmask, int busdays_in_weekmask,
                    npy_datetime *holidays_begin, npy_datetime *holidays_end)
{
    int day_of_week = 0;
    npy_datetime *holidays_temp;

    /* Roll the date to a business day */
    if (apply_business_day_roll(date, &date, &day_of_week,
                                roll,
                                weekmask,
                                holidays_begin, holidays_end) < 0) {
        return -1;
    }

    /* If we get a NaT, just return it */
    if (date == NPY_DATETIME_NAT) {
        *out = NPY_DATETIME_NAT;
        return 0;
    }

    /* Now we're on a valid business day */
    if (offset > 0) {
        /* Remove any earlier holidays */
        holidays_begin = find_earliest_holiday_on_or_after(date,
                                            holidays_begin, holidays_end);

        /* Jump by as many weeks as we can */
        date += (offset / busdays_in_weekmask) * 7;
        offset = offset % busdays_in_weekmask;

        /* Adjust based on the number of holidays we crossed */
        holidays_temp = find_earliest_holiday_after(date,
                                            holidays_begin, holidays_end);
        offset += holidays_temp - holidays_begin;
        holidays_begin = holidays_temp;

        /* Step until we use up the rest of the offset */
        while (offset > 0) {
            ++date;
            if (++day_of_week == 7) {
                day_of_week = 0;
            }
            if (weekmask[day_of_week] && !is_holiday(date,
                                            holidays_begin, holidays_end)) {
                offset--;
            }
        }
    }
    else if (offset < 0) {
        /* Remove any later holidays */
        holidays_end = find_earliest_holiday_after(date,
                                            holidays_begin, holidays_end);

        /* Jump by as many weeks as we can */
        date += (offset / busdays_in_weekmask) * 7;
        offset = offset % busdays_in_weekmask;

        /* Adjust based on the number of holidays we crossed */
        holidays_temp = find_earliest_holiday_on_or_after(date,
                                            holidays_begin, holidays_end);
        offset -= holidays_end - holidays_temp;
        holidays_end = holidays_temp;

        /* Step until we use up the rest of the offset */
        while (offset < 0) {
            --date;
            if (--day_of_week == -1) {
                day_of_week = 6;
            }
            if (weekmask[day_of_week] && !is_holiday(date,
                                            holidays_begin, holidays_end)) {
                offset++;
            }
        }
    }

    *out = date;
    return 0;
}