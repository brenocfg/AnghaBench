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
 scalar_t__ TRACE_ON ; 
 scalar_t__ monitor_hw ; 
 scalar_t__ trace_state ; 

__attribute__((used)) static bool net_dm_is_monitoring(void)
{
	return trace_state == TRACE_ON || monitor_hw;
}