#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* walsnds; int /*<<< orphan*/ * SyncRepQueue; } ;
typedef  TYPE_1__ WalSndCtlData ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ WalSnd ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_SYNC_REP_WAIT_MODE ; 
 int /*<<< orphan*/  SHMQueueInit (int /*<<< orphan*/ *) ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* WalSndCtl ; 
 int /*<<< orphan*/  WalSndShmemSize () ; 
 int max_wal_senders ; 

void
WalSndShmemInit(void)
{
	bool		found;
	int			i;

	WalSndCtl = (WalSndCtlData *)
		ShmemInitStruct("Wal Sender Ctl", WalSndShmemSize(), &found);

	if (!found)
	{
		/* First time through, so initialize */
		MemSet(WalSndCtl, 0, WalSndShmemSize());

		for (i = 0; i < NUM_SYNC_REP_WAIT_MODE; i++)
			SHMQueueInit(&(WalSndCtl->SyncRepQueue[i]));

		for (i = 0; i < max_wal_senders; i++)
		{
			WalSnd	   *walsnd = &WalSndCtl->walsnds[i];

			SpinLockInit(&walsnd->mutex);
		}
	}
}