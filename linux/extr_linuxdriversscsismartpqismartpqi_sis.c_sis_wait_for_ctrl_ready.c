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
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIS_CTRL_READY_TIMEOUT_SECS ; 
 int sis_wait_for_ctrl_ready_with_timeout (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 

int sis_wait_for_ctrl_ready(struct pqi_ctrl_info *ctrl_info)
{
	return sis_wait_for_ctrl_ready_with_timeout(ctrl_info,
		SIS_CTRL_READY_TIMEOUT_SECS);
}