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
struct timeval {int tv_sec; long long tv_usec; } ;
struct timespec {int tv_sec; long long tv_nsec; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;
typedef  long long DWORD ;

/* Variables and functions */
 long long INFINITE ; 
 int INT64_MAX ; 
 long long INT_MAX ; 
 int cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

int pthread_cond_timedwait(pthread_cond_t *restrict cond,
                           pthread_mutex_t *restrict mutex,
                           const struct timespec *restrict abstime)
{
    // mpv uses mingw's gettimeofday() as time source too.
    struct timeval tv;
    gettimeofday(&tv, NULL);
    DWORD timeout_ms = 0;
    if (abstime->tv_sec >= INT64_MAX / 10000) {
        timeout_ms = INFINITE;
    } else if (abstime->tv_sec >= tv.tv_sec) {
        long long msec = (abstime->tv_sec - tv.tv_sec) * 1000LL +
            abstime->tv_nsec / 1000LL / 1000LL - tv.tv_usec / 1000LL;
        if (msec > INT_MAX) {
            timeout_ms = INFINITE;
        } else if (msec > 0) {
            timeout_ms = msec;
        }
    }
    return cond_wait(cond, mutex, timeout_ms);
}