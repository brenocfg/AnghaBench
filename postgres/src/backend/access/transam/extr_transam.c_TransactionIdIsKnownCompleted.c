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
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cachedFetchXid ; 

bool
TransactionIdIsKnownCompleted(TransactionId transactionId)
{
	if (TransactionIdEquals(transactionId, cachedFetchXid))
	{
		/* If it's in the cache at all, it must be completed. */
		return true;
	}

	return false;
}