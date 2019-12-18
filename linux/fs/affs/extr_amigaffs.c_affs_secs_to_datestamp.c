#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ time64_t ;
struct affs_date {void* ticks; void* mins; void* days; } ;
typedef  int s32 ;
struct TYPE_2__ {int tz_minuteswest; } ;

/* Variables and functions */
 scalar_t__ AFFS_EPOCH_DELTA ; 
 void* cpu_to_be32 (int) ; 
 int div_s64_rem (scalar_t__,int,int*) ; 
 TYPE_1__ sys_tz ; 

void
affs_secs_to_datestamp(time64_t secs, struct affs_date *ds)
{
	u32	 days;
	u32	 minute;
	s32	 rem;

	secs -= sys_tz.tz_minuteswest * 60 + AFFS_EPOCH_DELTA;
	if (secs < 0)
		secs = 0;
	days    = div_s64_rem(secs, 86400, &rem);
	minute  = rem / 60;
	rem    -= minute * 60;

	ds->days = cpu_to_be32(days);
	ds->mins = cpu_to_be32(minute);
	ds->ticks = cpu_to_be32(rem * 50);
}