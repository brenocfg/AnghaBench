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
struct rtc_time {int dummy; } ;
struct cpcap_time {int tod1; int tod2; unsigned long day; } ;

/* Variables and functions */
 unsigned long DAY_MASK ; 
 unsigned long SECS_PER_DAY ; 
 int TOD1_MASK ; 
 int TOD2_MASK ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static void cpcap2rtc_time(struct rtc_time *rtc, struct cpcap_time *cpcap)
{
	unsigned long int tod;
	unsigned long int time;

	tod = (cpcap->tod1 & TOD1_MASK) | ((cpcap->tod2 & TOD2_MASK) << 8);
	time = tod + ((cpcap->day & DAY_MASK) * SECS_PER_DAY);

	rtc_time_to_tm(time, rtc);
}