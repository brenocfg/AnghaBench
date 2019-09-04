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
 int /*<<< orphan*/  PQI_RESCAN_WORK_DELAY ; 
 int /*<<< orphan*/  pqi_schedule_rescan_worker_with_delay (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pqi_schedule_rescan_worker_delayed(
	struct pqi_ctrl_info *ctrl_info)
{
	pqi_schedule_rescan_worker_with_delay(ctrl_info, PQI_RESCAN_WORK_DELAY);
}