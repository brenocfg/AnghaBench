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
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_LOCKTAG_TRANSACTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
XactLockTableDelete(TransactionId xid)
{
	LOCKTAG		tag;

	SET_LOCKTAG_TRANSACTION(tag, xid);

	LockRelease(&tag, ExclusiveLock, false);
}