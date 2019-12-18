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
struct TYPE_6__ {scalar_t__ addTemp; scalar_t__ addCatalog; int /*<<< orphan*/  schemas; } ;
struct TYPE_5__ {int /*<<< orphan*/  creationNamespace; int /*<<< orphan*/ * searchPath; int /*<<< orphan*/  nestLevel; } ;
typedef  TYPE_1__ OverrideStackEntry ;
typedef  TYPE_2__ OverrideSearchPath ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTransactionNestLevel () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATALOG_NAMESPACE ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  activeCreationNamespace ; 
 int /*<<< orphan*/ * activeSearchPath ; 
 int activeTempCreationPending ; 
 int /*<<< orphan*/  lcons (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lcons_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linitial_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myTempNamespace ; 
 int /*<<< orphan*/  overrideStack ; 
 scalar_t__ palloc (int) ; 

void
PushOverrideSearchPath(OverrideSearchPath *newpath)
{
	OverrideStackEntry *entry;
	List	   *oidlist;
	Oid			firstNS;
	MemoryContext oldcxt;

	/*
	 * Copy the list for safekeeping, and insert implicitly-searched
	 * namespaces as needed.  This code should track recomputeNamespacePath.
	 */
	oldcxt = MemoryContextSwitchTo(TopMemoryContext);

	oidlist = list_copy(newpath->schemas);

	/*
	 * Remember the first member of the explicit list.
	 */
	if (oidlist == NIL)
		firstNS = InvalidOid;
	else
		firstNS = linitial_oid(oidlist);

	/*
	 * Add any implicitly-searched namespaces to the list.  Note these go on
	 * the front, not the back; also notice that we do not check USAGE
	 * permissions for these.
	 */
	if (newpath->addCatalog)
		oidlist = lcons_oid(PG_CATALOG_NAMESPACE, oidlist);

	if (newpath->addTemp && OidIsValid(myTempNamespace))
		oidlist = lcons_oid(myTempNamespace, oidlist);

	/*
	 * Build the new stack entry, then insert it at the head of the list.
	 */
	entry = (OverrideStackEntry *) palloc(sizeof(OverrideStackEntry));
	entry->searchPath = oidlist;
	entry->creationNamespace = firstNS;
	entry->nestLevel = GetCurrentTransactionNestLevel();

	overrideStack = lcons(entry, overrideStack);

	/* And make it active. */
	activeSearchPath = entry->searchPath;
	activeCreationNamespace = entry->creationNamespace;
	activeTempCreationPending = false;	/* XXX is this OK? */

	MemoryContextSwitchTo(oldcxt);
}