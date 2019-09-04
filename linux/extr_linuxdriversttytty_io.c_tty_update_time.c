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
typedef  int time64_t ;
struct timespec64 {int tv_sec; } ;

/* Variables and functions */
 int ktime_get_real_seconds () ; 

__attribute__((used)) static void tty_update_time(struct timespec64 *time)
{
	time64_t sec = ktime_get_real_seconds();

	/*
	 * We only care if the two values differ in anything other than the
	 * lower three bits (i.e every 8 seconds).  If so, then we can update
	 * the time of the tty device, otherwise it could be construded as a
	 * security leak to let userspace know the exact timing of the tty.
	 */
	if ((sec ^ time->tv_sec) & ~7)
		time->tv_sec = sec;
}