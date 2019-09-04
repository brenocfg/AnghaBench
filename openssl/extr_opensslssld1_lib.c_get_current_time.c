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
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_current_time(struct timeval *t)
{
#if defined(_WIN32)
    SYSTEMTIME st;
    union {
        unsigned __int64 ul;
        FILETIME ft;
    } now;

    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &now.ft);
    /* re-bias to 1/1/1970 */
# ifdef  __MINGW32__
    now.ul -= 116444736000000000ULL;
# else
    /* *INDENT-OFF* */
    now.ul -= 116444736000000000UI64;
    /* *INDENT-ON* */
# endif
    t->tv_sec = (long)(now.ul / 10000000);
    t->tv_usec = ((int)(now.ul % 10000000)) / 10;
#else
    gettimeofday(t, NULL);
#endif
}