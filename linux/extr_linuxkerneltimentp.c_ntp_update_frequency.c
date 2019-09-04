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

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  NTP_INTERVAL_FREQ ; 
 int NTP_SCALE_SHIFT ; 
 int USER_HZ ; 
 int div_u64 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ntp_tick_adj ; 
 int /*<<< orphan*/  tick_length ; 
 int tick_length_base ; 
 int tick_nsec ; 
 int tick_usec ; 
 scalar_t__ time_freq ; 

__attribute__((used)) static void ntp_update_frequency(void)
{
	u64 second_length;
	u64 new_base;

	second_length		 = (u64)(tick_usec * NSEC_PER_USEC * USER_HZ)
						<< NTP_SCALE_SHIFT;

	second_length		+= ntp_tick_adj;
	second_length		+= time_freq;

	tick_nsec		 = div_u64(second_length, HZ) >> NTP_SCALE_SHIFT;
	new_base		 = div_u64(second_length, NTP_INTERVAL_FREQ);

	/*
	 * Don't wait for the next second_overflow, apply
	 * the change to the tick length immediately:
	 */
	tick_length		+= new_base - tick_length_base;
	tick_length_base	 = new_base;
}