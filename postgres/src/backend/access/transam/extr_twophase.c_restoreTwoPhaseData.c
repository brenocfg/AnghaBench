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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  scalar_t__ TransactionId ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidRepOriginId ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  PrepareRedoAdd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ProcessTwoPhaseBuffer (scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWOPHASE_DIR ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int strspn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
restoreTwoPhaseData(void)
{
	DIR		   *cldir;
	struct dirent *clde;

	LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
	cldir = AllocateDir(TWOPHASE_DIR);
	while ((clde = ReadDir(cldir, TWOPHASE_DIR)) != NULL)
	{
		if (strlen(clde->d_name) == 8 &&
			strspn(clde->d_name, "0123456789ABCDEF") == 8)
		{
			TransactionId xid;
			char	   *buf;

			xid = (TransactionId) strtoul(clde->d_name, NULL, 16);

			buf = ProcessTwoPhaseBuffer(xid, InvalidXLogRecPtr,
										true, false, false);
			if (buf == NULL)
				continue;

			PrepareRedoAdd(buf, InvalidXLogRecPtr,
						   InvalidXLogRecPtr, InvalidRepOriginId);
		}
	}
	LWLockRelease(TwoPhaseStateLock);
	FreeDir(cldir);
}