#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  disconnected; } ;
struct TYPE_8__ {scalar_t__ aborting; scalar_t__ disconnectable; } ;
struct TYPE_11__ {int /*<<< orphan*/ * origSCpnt; int /*<<< orphan*/ * rstSCpnt; int /*<<< orphan*/ * reqSCpnt; int /*<<< orphan*/ * SCpnt; TYPE_3__ queues; TYPE_2__* device; TYPE_1__ scsi; int /*<<< orphan*/  busyluns; } ;
struct TYPE_9__ {int parity_check; scalar_t__ parity_enabled; } ;
typedef  TYPE_4__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  fas216_bus_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * queue_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fas216_reset_state(FAS216_Info *info)
{
	int i;

	fas216_checkmagic(info);

	fas216_bus_reset(info);

	/*
	 * Clear out all stale info in our state structure
	 */
	memset(info->busyluns, 0, sizeof(info->busyluns));
	info->scsi.disconnectable = 0;
	info->scsi.aborting = 0;

	for (i = 0; i < 8; i++) {
		info->device[i].parity_enabled	= 0;
		info->device[i].parity_check	= 1;
	}

	/*
	 * Drain all commands on disconnected queue
	 */
	while (queue_remove(&info->queues.disconnected) != NULL);

	/*
	 * Remove executing commands.
	 */
	info->SCpnt     = NULL;
	info->reqSCpnt  = NULL;
	info->rstSCpnt  = NULL;
	info->origSCpnt = NULL;
}