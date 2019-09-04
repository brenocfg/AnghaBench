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
 scalar_t__ geteuid () ; 
 int perf_event_paranoid () ; 

__attribute__((used)) static bool perf_event_can_profile_kernel(void)
{
	return geteuid() == 0 || perf_event_paranoid() == -1;
}