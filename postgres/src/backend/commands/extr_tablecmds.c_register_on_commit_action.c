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
struct TYPE_3__ {int /*<<< orphan*/  deleting_subid; int /*<<< orphan*/  creating_subid; scalar_t__ oncommit; int /*<<< orphan*/  relid; } ;
typedef  TYPE_1__ OnCommitItem ;
typedef  scalar_t__ OnCommitAction ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  InvalidSubTransactionId ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ ONCOMMIT_NOOP ; 
 scalar_t__ ONCOMMIT_PRESERVE_ROWS ; 
 int /*<<< orphan*/  lcons (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_commits ; 
 scalar_t__ palloc (int) ; 

void
register_on_commit_action(Oid relid, OnCommitAction action)
{
	OnCommitItem *oc;
	MemoryContext oldcxt;

	/*
	 * We needn't bother registering the relation unless there is an ON COMMIT
	 * action we need to take.
	 */
	if (action == ONCOMMIT_NOOP || action == ONCOMMIT_PRESERVE_ROWS)
		return;

	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

	oc = (OnCommitItem *) palloc(sizeof(OnCommitItem));
	oc->relid = relid;
	oc->oncommit = action;
	oc->creating_subid = GetCurrentSubTransactionId();
	oc->deleting_subid = InvalidSubTransactionId;

	/*
	 * We use lcons() here so that ON COMMIT actions are processed in reverse
	 * order of registration.  That might not be essential but it seems
	 * reasonable.
	 */
	on_commits = lcons(oc, on_commits);

	MemoryContextSwitchTo(oldcxt);
}