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
struct TYPE_3__ {int phase; } ;
struct TYPE_4__ {TYPE_1__ SCp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLRSELTIMO ; 
 TYPE_2__* CURRENT_SC ; 
 int DID_ABORT ; 
 int DID_BUS_BUSY ; 
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SELINGO ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 scalar_t__ TESTLO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aborted ; 
 int /*<<< orphan*/  done (struct Scsi_Host*,int) ; 
 int selecting ; 

__attribute__((used)) static void selto_run(struct Scsi_Host *shpnt)
{
	SETPORT(SCSISEQ, 0);
	SETPORT(SSTAT1, CLRSELTIMO);

	if (!CURRENT_SC)
		return;

	CURRENT_SC->SCp.phase &= ~selecting;

	if (CURRENT_SC->SCp.phase & aborted)
		done(shpnt, DID_ABORT << 16);
	else if (TESTLO(SSTAT0, SELINGO))
		done(shpnt, DID_BUS_BUSY << 16);
	else
		/* ARBITRATION won, but SELECTION failed */
		done(shpnt, DID_NO_CONNECT << 16);
}