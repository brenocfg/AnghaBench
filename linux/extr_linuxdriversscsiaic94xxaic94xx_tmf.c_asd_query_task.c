#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  LUN; } ;
struct sas_task {TYPE_1__ ssp_task; int /*<<< orphan*/  dev; struct asd_ascb* lldd_task; } ;
struct asd_ascb {int tc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMF_QUERY_TASK ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int asd_initiate_ssp_tmf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int asd_query_task(struct sas_task *task)
{
	struct asd_ascb *ascb = task->lldd_task;
	int index;

	if (ascb) {
		index = ascb->tc_index;
		return asd_initiate_ssp_tmf(task->dev, task->ssp_task.LUN,
					    TMF_QUERY_TASK, index);
	}
	return TMF_RESP_FUNC_COMPLETE;
}