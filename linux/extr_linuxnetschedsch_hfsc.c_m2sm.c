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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int PSCHED_TICKS_PER_SEC ; 
 int SM_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static u64
m2sm(u32 m)
{
	u64 sm;

	sm = ((u64)m << SM_SHIFT);
	sm += PSCHED_TICKS_PER_SEC - 1;
	do_div(sm, PSCHED_TICKS_PER_SEC);
	return sm;
}