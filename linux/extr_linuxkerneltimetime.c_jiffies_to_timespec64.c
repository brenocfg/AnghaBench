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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int TICK_NSEC ; 
 int /*<<< orphan*/  div_u64_rem (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
jiffies_to_timespec64(const unsigned long jiffies, struct timespec64 *value)
{
	/*
	 * Convert jiffies to nanoseconds and separate with
	 * one divide.
	 */
	u32 rem;
	value->tv_sec = div_u64_rem((u64)jiffies * TICK_NSEC,
				    NSEC_PER_SEC, &rem);
	value->tv_nsec = rem;
}