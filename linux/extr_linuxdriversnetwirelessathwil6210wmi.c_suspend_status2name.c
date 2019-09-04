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
typedef  int u8 ;

/* Variables and functions */
#define  WMI_TRAFFIC_SUSPEND_REJECTED_LINK_NOT_IDLE 128 

__attribute__((used)) static const char *suspend_status2name(u8 status)
{
	switch (status) {
	case WMI_TRAFFIC_SUSPEND_REJECTED_LINK_NOT_IDLE:
		return "LINK_NOT_IDLE";
	default:
		return "Untracked status";
	}
}