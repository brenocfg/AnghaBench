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
struct timeval {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ now ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
update_time(void)
{
#if defined(_WIN32)
    /* on _WIN32, gettimeofday is faster than time(NULL) */
    struct timeval tv;
    if (!gettimeofday(&tv, NULL))
    {
        if (tv.tv_sec != now)
        {
            now = tv.tv_sec;
        }
    }
#else  /* if defined(_WIN32) */
    const time_t real_time = time(NULL);
    if (real_time != now)
    {
        now = real_time;
    }
#endif
}