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
typedef  int u32 ;

/* Variables and functions */
 int TCA_TAPRIO_ATTR_FLAG_FULL_OFFLOAD ; 
 int TCA_TAPRIO_ATTR_FLAG_TXTIME_ASSIST ; 

__attribute__((used)) static bool taprio_flags_valid(u32 flags)
{
	/* Make sure no other flag bits are set. */
	if (flags & ~(TCA_TAPRIO_ATTR_FLAG_TXTIME_ASSIST |
		      TCA_TAPRIO_ATTR_FLAG_FULL_OFFLOAD))
		return false;
	/* txtime-assist and full offload are mutually exclusive */
	if ((flags & TCA_TAPRIO_ATTR_FLAG_TXTIME_ASSIST) &&
	    (flags & TCA_TAPRIO_ATTR_FLAG_FULL_OFFLOAD))
		return false;
	return true;
}