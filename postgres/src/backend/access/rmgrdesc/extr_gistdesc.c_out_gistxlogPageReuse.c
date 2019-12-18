#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  relNode; int /*<<< orphan*/  dbNode; int /*<<< orphan*/  spcNode; } ;
struct TYPE_5__ {int /*<<< orphan*/  latestRemovedFullXid; int /*<<< orphan*/  block; TYPE_1__ node; } ;
typedef  TYPE_2__ gistxlogPageReuse ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
out_gistxlogPageReuse(StringInfo buf, gistxlogPageReuse *xlrec)
{
	appendStringInfo(buf, "rel %u/%u/%u; blk %u; latestRemovedXid %u:%u",
					 xlrec->node.spcNode, xlrec->node.dbNode,
					 xlrec->node.relNode, xlrec->block,
					 EpochFromFullTransactionId(xlrec->latestRemovedFullXid),
					 XidFromFullTransactionId(xlrec->latestRemovedFullXid));
}