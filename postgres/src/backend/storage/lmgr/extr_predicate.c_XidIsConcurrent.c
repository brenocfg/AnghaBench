#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  scalar_t__ TransactionId ;
struct TYPE_3__ {size_t xcnt; scalar_t__* xip; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
typedef  TYPE_1__* Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetTopTransactionIdIfAny () ; 
 TYPE_1__* GetTransactionSnapshot () ; 
 int /*<<< orphan*/  TransactionIdEquals (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdFollowsOrEquals (scalar_t__,int /*<<< orphan*/ ) ; 
 int TransactionIdIsValid (scalar_t__) ; 
 scalar_t__ TransactionIdPrecedes (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
XidIsConcurrent(TransactionId xid)
{
	Snapshot	snap;
	uint32		i;

	Assert(TransactionIdIsValid(xid));
	Assert(!TransactionIdEquals(xid, GetTopTransactionIdIfAny()));

	snap = GetTransactionSnapshot();

	if (TransactionIdPrecedes(xid, snap->xmin))
		return false;

	if (TransactionIdFollowsOrEquals(xid, snap->xmax))
		return true;

	for (i = 0; i < snap->xcnt; i++)
	{
		if (xid == snap->xip[i])
			return true;
	}

	return false;
}