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
 scalar_t__ SYSTEM_HALT ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 scalar_t__ SYSTEM_RESTART ; 
 scalar_t__ system_state ; 

__attribute__((used)) static bool system_going_down(void)
{
	return system_state == SYSTEM_HALT || system_state == SYSTEM_POWER_OFF
		|| system_state == SYSTEM_RESTART;
}