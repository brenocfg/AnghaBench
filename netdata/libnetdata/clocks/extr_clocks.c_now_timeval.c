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
typedef  scalar_t__ suseconds_t ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int NSEC_PER_USEC ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int now_timeval(clockid_t clk_id, struct timeval *tv) {
    struct timespec ts;

    if(unlikely(clock_gettime(clk_id, &ts) == -1)) {
        error("clock_gettime(%d, &timespec) failed.", clk_id);
        tv->tv_sec = 0;
        tv->tv_usec = 0;
        return -1;
    }

    tv->tv_sec = ts.tv_sec;
    tv->tv_usec = (suseconds_t)((ts.tv_nsec % NSEC_PER_SEC) / NSEC_PER_USEC);
    return 0;
}