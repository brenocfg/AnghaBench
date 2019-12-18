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

/* Variables and functions */
 scalar_t__ NPY_DATETIME_NAT ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__* find_earliest_holiday_on_or_after (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int get_day_of_week (scalar_t__) ; 

__attribute__((used)) static int
apply_business_day_count(npy_datetime date_begin, npy_datetime date_end,
                    npy_int64 *out,
                    const npy_bool *weekmask, int busdays_in_weekmask,
                    npy_datetime *holidays_begin, npy_datetime *holidays_end)
{
    npy_int64 count, whole_weeks;
    int day_of_week = 0;
    int swapped = 0;

    /* If we get a NaT, raise an error */
    if (date_begin == NPY_DATETIME_NAT || date_end == NPY_DATETIME_NAT) {
        PyErr_SetString(PyExc_ValueError,
                "Cannot compute a business day count with a NaT (not-a-time) "
                "date");
        return -1;
    }

    /* Trivial empty date range */
    if (date_begin == date_end) {
        *out = 0;
        return 0;
    }
    else if (date_begin > date_end) {
        npy_datetime tmp = date_begin;
        date_begin = date_end;
        date_end = tmp;
        swapped = 1;
    }

    /* Remove any earlier holidays */
    holidays_begin = find_earliest_holiday_on_or_after(date_begin,
                                        holidays_begin, holidays_end);
    /* Remove any later holidays */
    holidays_end = find_earliest_holiday_on_or_after(date_end,
                                        holidays_begin, holidays_end);

    /* Start the count as negative the number of holidays in the range */
    count = -(holidays_end - holidays_begin);

    /* Add the whole weeks between date_begin and date_end */
    whole_weeks = (date_end - date_begin) / 7;
    count += whole_weeks * busdays_in_weekmask;
    date_begin += whole_weeks * 7;

    if (date_begin < date_end) {
        /* Get the day of the week for 'date_begin' */
        day_of_week = get_day_of_week(date_begin);

        /* Count the remaining days one by one */
        while (date_begin < date_end) {
            if (weekmask[day_of_week]) {
                count++;
            }
            ++date_begin;
            if (++day_of_week == 7) {
                day_of_week = 0;
            }
        }
    }

    if (swapped) {
        count = -count;
    }

    *out = count;
    return 0;
}