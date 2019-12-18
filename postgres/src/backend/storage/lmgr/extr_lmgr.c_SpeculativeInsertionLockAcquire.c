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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  LockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SET_LOCKTAG_SPECULATIVE_INSERTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int speculativeInsertionToken ; 

uint32
SpeculativeInsertionLockAcquire(TransactionId xid)
{
	LOCKTAG		tag;

	speculativeInsertionToken++;

	/*
	 * Check for wrap-around. Zero means no token is held, so don't use that.
	 */
	if (speculativeInsertionToken == 0)
		speculativeInsertionToken = 1;

	SET_LOCKTAG_SPECULATIVE_INSERTION(tag, xid, speculativeInsertionToken);

	(void) LockAcquire(&tag, ExclusiveLock, false, false);

	return speculativeInsertionToken;
}