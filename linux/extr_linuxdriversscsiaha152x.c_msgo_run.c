#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  phase; } ;
struct TYPE_4__ {TYPE_1__ SCp; } ;

/* Variables and functions */
 int ABORT ; 
 int BUS_DEVICE_RESET ; 
 int CLRATNO ; 
 TYPE_2__* CURRENT_SC ; 
 int IDENTIFY_BASE ; 
 int MSGO (int) ; 
 int MSGOLEN ; 
 int MSGO_I ; 
 int /*<<< orphan*/  SCSIDAT ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPIORDY ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 scalar_t__ TESTLO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aborted ; 
 int /*<<< orphan*/  identified ; 
 int /*<<< orphan*/  resetted ; 

__attribute__((used)) static void msgo_run(struct Scsi_Host *shpnt)
{
	while(MSGO_I<MSGOLEN) {
		if (TESTLO(SSTAT0, SPIORDY))
			return;

		if (MSGO_I==MSGOLEN-1) {
			/* Leave MESSAGE OUT after transfer */
			SETPORT(SSTAT1, CLRATNO);
		}


		if (MSGO(MSGO_I) & IDENTIFY_BASE)
			CURRENT_SC->SCp.phase |= identified;

		if (MSGO(MSGO_I)==ABORT)
			CURRENT_SC->SCp.phase |= aborted;

		if (MSGO(MSGO_I)==BUS_DEVICE_RESET)
			CURRENT_SC->SCp.phase |= resetted;

		SETPORT(SCSIDAT, MSGO(MSGO_I++));
	}
}