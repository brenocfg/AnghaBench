#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char XidStatus ;
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {TYPE_1__* shared; } ;
struct TYPE_3__ {char** page_buffer; scalar_t__* group_lsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int CLOG_BITS_PER_XACT ; 
 char CLOG_XACT_BITMASK ; 
 TYPE_2__* ClogCtl ; 
 int GetLSNIndex (int,int /*<<< orphan*/ ) ; 
 scalar_t__ InRecovery ; 
 char TRANSACTION_STATUS_COMMITTED ; 
 char TRANSACTION_STATUS_IN_PROGRESS ; 
 char TRANSACTION_STATUS_SUB_COMMITTED ; 
 int TransactionIdToBIndex (int /*<<< orphan*/ ) ; 
 int TransactionIdToByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRecPtrIsInvalid (scalar_t__) ; 

__attribute__((used)) static void
TransactionIdSetStatusBit(TransactionId xid, XidStatus status, XLogRecPtr lsn, int slotno)
{
	int			byteno = TransactionIdToByte(xid);
	int			bshift = TransactionIdToBIndex(xid) * CLOG_BITS_PER_XACT;
	char	   *byteptr;
	char		byteval;
	char		curval;

	byteptr = ClogCtl->shared->page_buffer[slotno] + byteno;
	curval = (*byteptr >> bshift) & CLOG_XACT_BITMASK;

	/*
	 * When replaying transactions during recovery we still need to perform
	 * the two phases of subcommit and then commit. However, some transactions
	 * are already correctly marked, so we just treat those as a no-op which
	 * allows us to keep the following Assert as restrictive as possible.
	 */
	if (InRecovery && status == TRANSACTION_STATUS_SUB_COMMITTED &&
		curval == TRANSACTION_STATUS_COMMITTED)
		return;

	/*
	 * Current state change should be from 0 or subcommitted to target state
	 * or we should already be there when replaying changes during recovery.
	 */
	Assert(curval == 0 ||
		   (curval == TRANSACTION_STATUS_SUB_COMMITTED &&
			status != TRANSACTION_STATUS_IN_PROGRESS) ||
		   curval == status);

	/* note this assumes exclusive access to the clog page */
	byteval = *byteptr;
	byteval &= ~(((1 << CLOG_BITS_PER_XACT) - 1) << bshift);
	byteval |= (status << bshift);
	*byteptr = byteval;

	/*
	 * Update the group LSN if the transaction completion LSN is higher.
	 *
	 * Note: lsn will be invalid when supplied during InRecovery processing,
	 * so we don't need to do anything special to avoid LSN updates during
	 * recovery. After recovery completes the next clog change will set the
	 * LSN correctly.
	 */
	if (!XLogRecPtrIsInvalid(lsn))
	{
		int			lsnindex = GetLSNIndex(slotno, xid);

		if (ClogCtl->shared->group_lsn[lsnindex] < lsn)
			ClogCtl->shared->group_lsn[lsnindex] = lsn;
	}
}