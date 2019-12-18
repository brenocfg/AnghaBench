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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_LOCKTAG_SPECULATIVE_INSERTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 

void
SpeculativeInsertionWait(TransactionId xid, uint32 token)
{
	LOCKTAG		tag;

	SET_LOCKTAG_SPECULATIVE_INSERTION(tag, xid, token);

	Assert(TransactionIdIsValid(xid));
	Assert(token != 0);

	(void) LockAcquire(&tag, ShareLock, false, false);
	LockRelease(&tag, ShareLock, false);
}