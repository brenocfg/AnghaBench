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

__attribute__((used)) static int64_t timespec_to_us64(struct timespec *ts)
{
	return ts->tv_sec * 1000 * 1000 + ts->tv_nsec / 1000;
}