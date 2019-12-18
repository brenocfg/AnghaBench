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

/* Variables and functions */
 int PSCHED_TICKS_PER_SEC ; 
 int SM_SHIFT ; 

__attribute__((used)) static u32
sm2m(u64 sm)
{
	u64 m;

	m = (sm * PSCHED_TICKS_PER_SEC) >> SM_SHIFT;
	return (u32)m;
}