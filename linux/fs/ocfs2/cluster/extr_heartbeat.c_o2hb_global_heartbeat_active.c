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
 scalar_t__ O2HB_HEARTBEAT_GLOBAL ; 
 scalar_t__ o2hb_heartbeat_mode ; 

int o2hb_global_heartbeat_active(void)
{
	return (o2hb_heartbeat_mode == O2HB_HEARTBEAT_GLOBAL);
}