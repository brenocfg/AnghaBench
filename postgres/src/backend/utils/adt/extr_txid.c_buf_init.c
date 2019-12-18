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
typedef  void* txid ;
struct TYPE_2__ {scalar_t__ nxip; void* xmax; void* xmin; } ;
typedef  TYPE_1__ TxidSnapshot ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TXID_SNAPSHOT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeStringInfo () ; 

__attribute__((used)) static StringInfo
buf_init(txid xmin, txid xmax)
{
	TxidSnapshot snap;
	StringInfo	buf;

	snap.xmin = xmin;
	snap.xmax = xmax;
	snap.nxip = 0;

	buf = makeStringInfo();
	appendBinaryStringInfo(buf, (char *) &snap, TXID_SNAPSHOT_SIZE(0));
	return buf;
}