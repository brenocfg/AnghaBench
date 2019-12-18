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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int xcnt; int xcnt_space; int /*<<< orphan*/ * xip; } ;
struct TYPE_5__ {TYPE_1__ committed; } ;
typedef  TYPE_2__ SnapBuild ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * repalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
SnapBuildAddCommittedTxn(SnapBuild *builder, TransactionId xid)
{
	Assert(TransactionIdIsValid(xid));

	if (builder->committed.xcnt == builder->committed.xcnt_space)
	{
		builder->committed.xcnt_space = builder->committed.xcnt_space * 2 + 1;

		elog(DEBUG1, "increasing space for committed transactions to %u",
			 (uint32) builder->committed.xcnt_space);

		builder->committed.xip = repalloc(builder->committed.xip,
										  builder->committed.xcnt_space * sizeof(TransactionId));
	}

	/*
	 * TODO: It might make sense to keep the array sorted here instead of
	 * doing it every time we build a new snapshot. On the other hand this
	 * gets called repeatedly when a transaction with subtransactions commits.
	 */
	builder->committed.xip[builder->committed.xcnt++] = xid;
}