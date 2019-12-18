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
typedef  scalar_t__ TransactionId ;
struct TYPE_2__ {scalar_t__ oldestCommitTsXid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTsLock ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* ShmemVariableCache ; 
 scalar_t__ TransactionIdPrecedes (scalar_t__,scalar_t__) ; 

void
AdvanceOldestCommitTsXid(TransactionId oldestXact)
{
	LWLockAcquire(CommitTsLock, LW_EXCLUSIVE);
	if (ShmemVariableCache->oldestCommitTsXid != InvalidTransactionId &&
		TransactionIdPrecedes(ShmemVariableCache->oldestCommitTsXid, oldestXact))
		ShmemVariableCache->oldestCommitTsXid = oldestXact;
	LWLockRelease(CommitTsLock);
}