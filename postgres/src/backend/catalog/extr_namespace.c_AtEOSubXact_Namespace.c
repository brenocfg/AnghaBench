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
struct TYPE_4__ {scalar_t__ nestLevel; int /*<<< orphan*/  creationNamespace; int /*<<< orphan*/  searchPath; } ;
typedef  scalar_t__ SubTransactionId ;
typedef  TYPE_1__ OverrideStackEntry ;

/* Variables and functions */
 scalar_t__ GetCurrentTransactionNestLevel () ; 
 void* InvalidOid ; 
 scalar_t__ InvalidSubTransactionId ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  activeCreationNamespace ; 
 int /*<<< orphan*/  activeSearchPath ; 
 int activeTempCreationPending ; 
 int /*<<< orphan*/  baseCreationNamespace ; 
 int /*<<< orphan*/  baseSearchPath ; 
 int baseSearchPathValid ; 
 int baseTempCreationPending ; 
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
AtEOSubXact_Namespace(bool isCommit, SubTransactionId mySubid,
					  SubTransactionId parentSubid)
{
	OverrideStackEntry *entry;

	if (myTempNamespaceSubID == mySubid)
	{
		if (isCommit)
			myTempNamespaceSubID = parentSubid;
		else
		{
			myTempNamespaceSubID = InvalidSubTransactionId;
			/* TEMP namespace creation failed, so reset state */
			myTempNamespace = InvalidOid;
			myTempToastNamespace = InvalidOid;
			baseSearchPathValid = false;	/* need to rebuild list */

			/*
			 * Reset the temporary namespace flag in MyProc.  We assume that
			 * this operation is atomic.
			 *
			 * Because this subtransaction is aborting, the pg_namespace row
			 * is not visible to anyone else anyway, but that doesn't matter:
			 * it's not a problem if objects contained in this namespace are
			 * removed concurrently.
			 */
			MyProc->tempNamespaceId = InvalidOid;
		}
	}

	/*
	 * Clean up if someone failed to do PopOverrideSearchPath
	 */
	while (overrideStack)
	{
		entry = (OverrideStackEntry *) linitial(overrideStack);
		if (entry->nestLevel < GetCurrentTransactionNestLevel())
			break;
		if (isCommit)
			elog(WARNING, "leaked override search path");
		overrideStack = list_delete_first(overrideStack);
		list_free(entry->searchPath);
		pfree(entry);
	}

	/* Activate the next level down. */
	if (overrideStack)
	{
		entry = (OverrideStackEntry *) linitial(overrideStack);
		activeSearchPath = entry->searchPath;
		activeCreationNamespace = entry->creationNamespace;
		activeTempCreationPending = false;	/* XXX is this OK? */
	}
	else
	{
		/* If not baseSearchPathValid, this is useless but harmless */
		activeSearchPath = baseSearchPath;
		activeCreationNamespace = baseCreationNamespace;
		activeTempCreationPending = baseTempCreationPending;
	}
}