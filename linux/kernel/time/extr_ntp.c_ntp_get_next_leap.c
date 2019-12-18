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
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  KTIME_MAX ; 
 int STA_INS ; 
 scalar_t__ TIME_INS ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntp_next_leap_sec ; 
 scalar_t__ time_state ; 
 int time_status ; 

ktime_t ntp_get_next_leap(void)
{
	ktime_t ret;

	if ((time_state == TIME_INS) && (time_status & STA_INS))
		return ktime_set(ntp_next_leap_sec, 0);
	ret = KTIME_MAX;
	return ret;
}