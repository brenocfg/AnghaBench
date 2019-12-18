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
 int CREDITS_PER_JIFFY ; 
 int CREDITS_PER_JIFFY_v1 ; 
 int HZ ; 
 int XT_HASHLIMIT_SCALE ; 
 int XT_HASHLIMIT_SCALE_v2 ; 
 int div64_u64 (int,int) ; 

__attribute__((used)) static u64 user2credits(u64 user, int revision)
{
	u64 scale = (revision == 1) ?
		XT_HASHLIMIT_SCALE : XT_HASHLIMIT_SCALE_v2;
	u64 cpj = (revision == 1) ?
		CREDITS_PER_JIFFY_v1 : CREDITS_PER_JIFFY;

	/* Avoid overflow: divide the constant operands first */
	if (scale >= HZ * cpj)
		return div64_u64(user, div64_u64(scale, HZ * cpj));

	return user * div64_u64(HZ * cpj, scale);
}