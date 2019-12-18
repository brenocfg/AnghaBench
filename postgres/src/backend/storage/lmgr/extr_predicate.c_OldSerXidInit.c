#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int do_fsync; int /*<<< orphan*/  PagePrecedes; } ;
struct TYPE_5__ {int headPage; void* tailXid; void* headXid; } ;
typedef  int /*<<< orphan*/  OldSerXidControlData ;
typedef  TYPE_1__* OldSerXidControl ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 void* InvalidTransactionId ; 
 int IsUnderPostmaster ; 
 int /*<<< orphan*/  LWTRANCHE_OLDSERXID_BUFFERS ; 
 int /*<<< orphan*/  NUM_OLDSERXID_BUFFERS ; 
 int /*<<< orphan*/  OldSerXidLock ; 
 int /*<<< orphan*/  OldSerXidPagePrecedesLogically ; 
 TYPE_3__* OldSerXidSlruCtl ; 
 scalar_t__ ShmemInitStruct (char*,int,int*) ; 
 int /*<<< orphan*/  SimpleLruInit (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* oldSerXidControl ; 

__attribute__((used)) static void
OldSerXidInit(void)
{
	bool		found;

	/*
	 * Set up SLRU management of the pg_serial data.
	 */
	OldSerXidSlruCtl->PagePrecedes = OldSerXidPagePrecedesLogically;
	SimpleLruInit(OldSerXidSlruCtl, "oldserxid",
				  NUM_OLDSERXID_BUFFERS, 0, OldSerXidLock, "pg_serial",
				  LWTRANCHE_OLDSERXID_BUFFERS);
	/* Override default assumption that writes should be fsync'd */
	OldSerXidSlruCtl->do_fsync = false;

	/*
	 * Create or attach to the OldSerXidControl structure.
	 */
	oldSerXidControl = (OldSerXidControl)
		ShmemInitStruct("OldSerXidControlData", sizeof(OldSerXidControlData), &found);

	Assert(found == IsUnderPostmaster);
	if (!found)
	{
		/*
		 * Set control information to reflect empty SLRU.
		 */
		oldSerXidControl->headPage = -1;
		oldSerXidControl->headXid = InvalidTransactionId;
		oldSerXidControl->tailXid = InvalidTransactionId;
	}
}