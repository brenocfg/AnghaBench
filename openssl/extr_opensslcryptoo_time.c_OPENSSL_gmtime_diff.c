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
struct tm {int dummy; } ;

/* Variables and functions */
 scalar_t__ SECS_PER_DAY ; 
 int /*<<< orphan*/  julian_adj (struct tm const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,int*) ; 

int OPENSSL_gmtime_diff(int *pday, int *psec,
                        const struct tm *from, const struct tm *to)
{
    int from_sec, to_sec, diff_sec;
    long from_jd, to_jd, diff_day;
    if (!julian_adj(from, 0, 0, &from_jd, &from_sec))
        return 0;
    if (!julian_adj(to, 0, 0, &to_jd, &to_sec))
        return 0;
    diff_day = to_jd - from_jd;
    diff_sec = to_sec - from_sec;
    /* Adjust differences so both positive or both negative */
    if (diff_day > 0 && diff_sec < 0) {
        diff_day--;
        diff_sec += SECS_PER_DAY;
    }
    if (diff_day < 0 && diff_sec > 0) {
        diff_day++;
        diff_sec -= SECS_PER_DAY;
    }

    if (pday)
        *pday = (int)diff_day;
    if (psec)
        *psec = diff_sec;

    return 1;

}