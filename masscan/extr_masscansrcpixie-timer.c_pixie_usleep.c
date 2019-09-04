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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ts ;
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (struct timespec*,struct timespec*,int) ; 
 int nanosleep (struct timespec*,struct timespec*) ; 

void
pixie_usleep(uint64_t microseconds)
{
    struct timespec ts;
    struct timespec remaining;
    int err;

    ts.tv_sec  =  microseconds/1000000;
    ts.tv_nsec = (microseconds%1000000) * 1000;

again:
    err = nanosleep(&ts, &remaining);
    if (err == -1 && errno == EINTR) {
        memcpy(&ts, &remaining, sizeof(ts));
        goto again;
    }

    //usleep(microseconds);
}