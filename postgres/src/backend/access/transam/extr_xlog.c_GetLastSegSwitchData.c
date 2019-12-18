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
typedef  int /*<<< orphan*/  pg_time_t ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_2__ {int /*<<< orphan*/  lastSegSwitchLSN; int /*<<< orphan*/  lastSegSwitchTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  WALWriteLock ; 
 TYPE_1__* XLogCtl ; 

pg_time_t
GetLastSegSwitchData(XLogRecPtr *lastSwitchLSN)
{
	pg_time_t	result;

	/* Need WALWriteLock, but shared lock is sufficient */
	LWLockAcquire(WALWriteLock, LW_SHARED);
	result = XLogCtl->lastSegSwitchTime;
	*lastSwitchLSN = XLogCtl->lastSegSwitchLSN;
	LWLockRelease(WALWriteLock);

	return result;
}