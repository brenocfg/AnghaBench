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
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 

void mp_sleep_us(int64_t us)
{
    if (us < 0)
        return;
    struct timespec ts;
    ts.tv_sec  =  us / 1000000;
    ts.tv_nsec = (us % 1000000) * 1000;
    nanosleep(&ts, NULL);
}