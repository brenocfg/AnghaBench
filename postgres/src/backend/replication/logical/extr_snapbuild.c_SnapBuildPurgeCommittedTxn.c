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
struct TYPE_4__ {int xcnt; int /*<<< orphan*/ * xip; } ;
struct TYPE_5__ {TYPE_1__ committed; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ SnapBuild ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/ * MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NormalTransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
SnapBuildPurgeCommittedTxn(SnapBuild *builder)
{
	int			off;
	TransactionId *workspace;
	int			surviving_xids = 0;

	/* not ready yet */
	if (!TransactionIdIsNormal(builder->xmin))
		return;

	/* TODO: Neater algorithm than just copying and iterating? */
	workspace =
		MemoryContextAlloc(builder->context,
						   builder->committed.xcnt * sizeof(TransactionId));

	/* copy xids that still are interesting to workspace */
	for (off = 0; off < builder->committed.xcnt; off++)
	{
		if (NormalTransactionIdPrecedes(builder->committed.xip[off],
										builder->xmin))
			;					/* remove */
		else
			workspace[surviving_xids++] = builder->committed.xip[off];
	}

	/* copy workspace back to persistent state */
	memcpy(builder->committed.xip, workspace,
		   surviving_xids * sizeof(TransactionId));

	elog(DEBUG3, "purged committed transactions from %u to %u, xmin: %u, xmax: %u",
		 (uint32) builder->committed.xcnt, (uint32) surviving_xids,
		 builder->xmin, builder->xmax);
	builder->committed.xcnt = surviving_xids;

	pfree(workspace);
}