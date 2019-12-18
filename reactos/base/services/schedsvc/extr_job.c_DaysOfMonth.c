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
typedef  int WORD ;

/* Variables and functions */

__attribute__((used)) static
WORD
DaysOfMonth(
    WORD wMonth,
    WORD wYear)
{
    WORD wDaysArray[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (wMonth == 2 && wYear % 4 == 0 && wYear % 400 != 0)
        return 29;

    return wDaysArray[wMonth];
}