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

/* Variables and functions */
 int /*<<< orphan*/  errno_assert (int) ; 
 int nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 

void nn_sleep (int milliseconds)
{
    int rc;
    struct timespec ts;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = milliseconds % 1000 * 1000000;
    rc = nanosleep (&ts, NULL);
    errno_assert (rc == 0);    
}