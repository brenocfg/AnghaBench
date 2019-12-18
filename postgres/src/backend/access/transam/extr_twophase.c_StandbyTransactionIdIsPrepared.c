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
struct TYPE_2__ {int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ TwoPhaseFileHeader ;
typedef  int /*<<< orphan*/  TransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* ReadTwoPhaseFile (int /*<<< orphan*/ ,int) ; 
 int TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ max_prepared_xacts ; 
 int /*<<< orphan*/  pfree (char*) ; 

bool
StandbyTransactionIdIsPrepared(TransactionId xid)
{
	char	   *buf;
	TwoPhaseFileHeader *hdr;
	bool		result;

	Assert(TransactionIdIsValid(xid));

	if (max_prepared_xacts <= 0)
		return false;			/* nothing to do */

	/* Read and validate file */
	buf = ReadTwoPhaseFile(xid, true);
	if (buf == NULL)
		return false;

	/* Check header also */
	hdr = (TwoPhaseFileHeader *) buf;
	result = TransactionIdEquals(hdr->xid, xid);
	pfree(buf);

	return result;
}