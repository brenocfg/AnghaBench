#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ SxactGlobalXmin; int SxactGlobalXminCount; } ;
struct TYPE_9__ {scalar_t__ xmin; } ;
typedef  TYPE_1__ SERIALIZABLEXACT ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* FirstPredXact () ; 
 scalar_t__ InvalidTransactionId ; 
 int LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 TYPE_1__* NextPredXact (TYPE_1__*) ; 
 TYPE_1__* OldCommittedSxact ; 
 int /*<<< orphan*/  OldSerXidSetActiveSerXmin (scalar_t__) ; 
 TYPE_4__* PredXact ; 
 int /*<<< orphan*/  SerializableXactHashLock ; 
 int /*<<< orphan*/  SxactIsCommitted (TYPE_1__*) ; 
 int /*<<< orphan*/  SxactIsRolledBack (TYPE_1__*) ; 
 scalar_t__ TransactionIdEquals (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdIsValid (scalar_t__) ; 
 scalar_t__ TransactionIdPrecedes (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
SetNewSxactGlobalXmin(void)
{
	SERIALIZABLEXACT *sxact;

	Assert(LWLockHeldByMe(SerializableXactHashLock));

	PredXact->SxactGlobalXmin = InvalidTransactionId;
	PredXact->SxactGlobalXminCount = 0;

	for (sxact = FirstPredXact(); sxact != NULL; sxact = NextPredXact(sxact))
	{
		if (!SxactIsRolledBack(sxact)
			&& !SxactIsCommitted(sxact)
			&& sxact != OldCommittedSxact)
		{
			Assert(sxact->xmin != InvalidTransactionId);
			if (!TransactionIdIsValid(PredXact->SxactGlobalXmin)
				|| TransactionIdPrecedes(sxact->xmin,
										 PredXact->SxactGlobalXmin))
			{
				PredXact->SxactGlobalXmin = sxact->xmin;
				PredXact->SxactGlobalXminCount = 1;
			}
			else if (TransactionIdEquals(sxact->xmin,
										 PredXact->SxactGlobalXmin))
				PredXact->SxactGlobalXminCount++;
		}
	}

	OldSerXidSetActiveSerXmin(PredXact->SxactGlobalXmin);
}