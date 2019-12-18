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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  ReorderBufferTXNByXid (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
ReorderBufferProcessXid(ReorderBuffer *rb, TransactionId xid, XLogRecPtr lsn)
{
	/* many records won't have an xid assigned, centralize check here */
	if (xid != InvalidTransactionId)
		ReorderBufferTXNByXid(rb, xid, true, NULL, lsn, true);
}