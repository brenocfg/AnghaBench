#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xid ;
typedef  int /*<<< orphan*/  txid ;
struct TYPE_5__ {int /*<<< orphan*/  nxip; } ;
typedef  TYPE_1__ TxidSnapshot ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_2__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_2__*,char*,int) ; 

__attribute__((used)) static void
buf_add_txid(StringInfo buf, txid xid)
{
	TxidSnapshot *snap = (TxidSnapshot *) buf->data;

	/* do this before possible realloc */
	snap->nxip++;

	appendBinaryStringInfo(buf, (char *) &xid, sizeof(xid));
}