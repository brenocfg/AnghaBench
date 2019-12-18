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
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_2__ {int tailKnownAssignedXids; int headKnownAssignedXids; int /*<<< orphan*/  known_assigned_xids_lck; } ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/ * KnownAssignedXids ; 
 scalar_t__* KnownAssignedXidsValid ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* procArray ; 

__attribute__((used)) static TransactionId
KnownAssignedXidsGetOldestXmin(void)
{
	int			head,
				tail;
	int			i;

	/*
	 * Fetch head just once, since it may change while we loop.
	 */
	SpinLockAcquire(&procArray->known_assigned_xids_lck);
	tail = procArray->tailKnownAssignedXids;
	head = procArray->headKnownAssignedXids;
	SpinLockRelease(&procArray->known_assigned_xids_lck);

	for (i = tail; i < head; i++)
	{
		/* Skip any gaps in the array */
		if (KnownAssignedXidsValid[i])
			return KnownAssignedXids[i];
	}

	return InvalidTransactionId;
}