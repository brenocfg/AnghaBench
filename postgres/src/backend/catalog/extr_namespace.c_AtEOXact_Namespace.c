#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* tempNamespaceId; } ;
struct TYPE_4__ {int /*<<< orphan*/  searchPath; } ;
typedef  TYPE_1__ OverrideStackEntry ;

/* Variables and functions */
 void* InvalidOid ; 
 scalar_t__ InvalidSubTransactionId ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  RemoveTempRelationsCallback ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  activeCreationNamespace ; 
 int /*<<< orphan*/  activeSearchPath ; 
 int /*<<< orphan*/  activeTempCreationPending ; 
 int /*<<< orphan*/  baseCreationNamespace ; 
 int /*<<< orphan*/  baseSearchPath ; 
 int baseSearchPathValid ; 
 int /*<<< orphan*/  baseTempCreationPending ; 
 int /*<<< orphan*/  before_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 void* myTempNamespace ; 
 scalar_t__ myTempNamespaceSubID ; 
 void* myTempToastNamespace ; 
 scalar_t__ overrideStack ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
AtEOXact_Namespace(bool isCommit, bool parallel)
{
	/*
	 * If we abort the transaction in which a temp namespace was selected,
	 * we'll have to do any creation or cleanout work over again.  So, just
	 * forget the namespace entirely until next time.  On the other hand, if
	 * we commit then register an exit callback to clean out the temp tables
	 * at backend shutdown.  (We only want to register the callback once per
	 * session, so this is a good place to do it.)
	 */
	if (myTempNamespaceSubID != InvalidSubTransactionId && !parallel)
	{
		if (isCommit)
			before_shmem_exit(RemoveTempRelationsCallback, 0);
		else
		{
			myTempNamespace = InvalidOid;
			myTempToastNamespace = InvalidOid;
			baseSearchPathValid = false;	/* need to rebuild list */

			/*
			 * Reset the temporary namespace flag in MyProc.  We assume that
			 * this operation is atomic.
			 *
			 * Because this transaction is aborting, the pg_namespace row is
			 * not visible to anyone else anyway, but that doesn't matter:
			 * it's not a problem if objects contained in this namespace are
			 * removed concurrently.
			 */
			MyProc->tempNamespaceId = InvalidOid;
		}
		myTempNamespaceSubID = InvalidSubTransactionId;
	}

	/*
	 * Clean up if someone failed to do PopOverrideSearchPath
	 */
	if (overrideStack)
	{
		if (isCommit)
			elog(WARNING, "leaked override search path");
		while (overrideStack)
		{
			OverrideStackEntry *entry;

			entry = (OverrideStackEntry *) linitial(overrideStack);
			overrideStack = list_delete_first(overrideStack);
			list_free(entry->searchPath);
			pfree(entry);
		}
		/* If not baseSearchPathValid, this is useless but harmless */
		activeSearchPath = baseSearchPath;
		activeCreationNamespace = baseCreationNamespace;
		activeTempCreationPending = baseTempCreationPending;
	}
}