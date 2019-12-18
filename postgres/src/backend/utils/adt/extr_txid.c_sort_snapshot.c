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
typedef  int /*<<< orphan*/  txid ;
struct TYPE_3__ {int nxip; int /*<<< orphan*/  xip; } ;
typedef  TYPE_1__ TxidSnapshot ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_txid ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int qunique (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sort_snapshot(TxidSnapshot *snap)
{
	if (snap->nxip > 1)
	{
		qsort(snap->xip, snap->nxip, sizeof(txid), cmp_txid);
		snap->nxip = qunique(snap->xip, snap->nxip, sizeof(txid), cmp_txid);
	}
}