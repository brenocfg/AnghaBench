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
struct TYPE_3__ {scalar_t__ nestLevel; int /*<<< orphan*/  creationNamespace; int /*<<< orphan*/  searchPath; } ;
typedef  TYPE_1__ OverrideStackEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetCurrentTransactionNestLevel () ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  activeCreationNamespace ; 
 int /*<<< orphan*/  activeSearchPath ; 
 int activeTempCreationPending ; 
 int /*<<< orphan*/  baseCreationNamespace ; 
 int /*<<< orphan*/  baseSearchPath ; 
 int baseTempCreationPending ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 scalar_t__ overrideStack ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
PopOverrideSearchPath(void)
{
	OverrideStackEntry *entry;

	/* Sanity checks. */
	if (overrideStack == NIL)
		elog(ERROR, "bogus PopOverrideSearchPath call");
	entry = (OverrideStackEntry *) linitial(overrideStack);
	if (entry->nestLevel != GetCurrentTransactionNestLevel())
		elog(ERROR, "bogus PopOverrideSearchPath call");

	/* Pop the stack and free storage. */
	overrideStack = list_delete_first(overrideStack);
	list_free(entry->searchPath);
	pfree(entry);

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