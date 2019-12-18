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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_3__ {int has_catalog_changes; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 TYPE_1__* ReorderBufferTXNByXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
ReorderBufferXidSetCatalogChanges(ReorderBuffer *rb, TransactionId xid,
								  XLogRecPtr lsn)
{
	ReorderBufferTXN *txn;

	txn = ReorderBufferTXNByXid(rb, xid, true, NULL, lsn, true);

	txn->has_catalog_changes = true;
}