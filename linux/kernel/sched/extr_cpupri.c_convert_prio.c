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

/* Variables and functions */
 int CPUPRI_IDLE ; 
 int CPUPRI_INVALID ; 
 int CPUPRI_NORMAL ; 
 int MAX_PRIO ; 
 int MAX_RT_PRIO ; 

__attribute__((used)) static int convert_prio(int prio)
{
	int cpupri;

	if (prio == CPUPRI_INVALID)
		cpupri = CPUPRI_INVALID;
	else if (prio == MAX_PRIO)
		cpupri = CPUPRI_IDLE;
	else if (prio >= MAX_RT_PRIO)
		cpupri = CPUPRI_NORMAL;
	else
		cpupri = MAX_RT_PRIO - prio + 1;

	return cpupri;
}