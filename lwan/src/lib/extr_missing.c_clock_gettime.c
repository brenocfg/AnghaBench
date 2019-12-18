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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int clockid_t ;

/* Variables and functions */
#define  CLOCK_MONOTONIC 129 
#define  CLOCK_MONOTONIC_COARSE 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int clock_gettime(clockid_t clk_id, struct timespec *ts)
{
    switch (clk_id) {
    case CLOCK_MONOTONIC:
    case CLOCK_MONOTONIC_COARSE:
        /* FIXME: time() isn't monotonic */
        ts->tv_sec = time(NULL);
        ts->tv_nsec = 0;
        return 0;
    }

    errno = EINVAL;
    return -1;
}