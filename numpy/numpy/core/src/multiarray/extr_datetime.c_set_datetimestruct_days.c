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
typedef  int npy_int64 ;
struct TYPE_3__ {int month; int day; int /*<<< orphan*/  year; } ;
typedef  TYPE_1__ npy_datetimestruct ;

/* Variables and functions */
 int** _days_per_month_table ; 
 int /*<<< orphan*/  days_to_yearsdays (int*) ; 
 size_t is_leapyear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_datetimestruct_days(npy_int64 days, npy_datetimestruct *dts)
{
    int *month_lengths, i;

    dts->year = days_to_yearsdays(&days);
    month_lengths = _days_per_month_table[is_leapyear(dts->year)];

    for (i = 0; i < 12; ++i) {
        if (days < month_lengths[i]) {
            dts->month = i + 1;
            dts->day = (int)days + 1;
            return;
        }
        else {
            days -= month_lengths[i];
        }
    }
}