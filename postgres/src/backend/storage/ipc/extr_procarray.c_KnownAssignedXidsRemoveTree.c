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

/* Variables and functions */
 int /*<<< orphan*/  KnownAssignedXidsCompress (int) ; 
 int /*<<< orphan*/  KnownAssignedXidsRemove (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
KnownAssignedXidsRemoveTree(TransactionId xid, int nsubxids,
							TransactionId *subxids)
{
	int			i;

	if (TransactionIdIsValid(xid))
		KnownAssignedXidsRemove(xid);

	for (i = 0; i < nsubxids; i++)
		KnownAssignedXidsRemove(subxids[i]);

	/* Opportunistically compress the array */
	KnownAssignedXidsCompress(false);
}