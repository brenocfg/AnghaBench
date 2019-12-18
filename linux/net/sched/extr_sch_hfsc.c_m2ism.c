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
 int HT_INFINITY ; 
 int ISM_SHIFT ; 
 scalar_t__ PSCHED_TICKS_PER_SEC ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
m2ism(u32 m)
{
	u64 ism;

	if (m == 0)
		ism = HT_INFINITY;
	else {
		ism = ((u64)PSCHED_TICKS_PER_SEC << ISM_SHIFT);
		ism += m - 1;
		do_div(ism, m);
	}
	return ism;
}