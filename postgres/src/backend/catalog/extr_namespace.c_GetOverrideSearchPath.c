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
struct TYPE_3__ {int addTemp; int addCatalog; int /*<<< orphan*/ * schemas; } ;
typedef  TYPE_1__ OverrideSearchPath ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_CATALOG_NAMESPACE ; 
 scalar_t__ activeCreationNamespace ; 
 int /*<<< orphan*/  activeSearchPath ; 
 scalar_t__ linitial_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 
 scalar_t__ myTempNamespace ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  recomputeNamespacePath () ; 

OverrideSearchPath *
GetOverrideSearchPath(MemoryContext context)
{
	OverrideSearchPath *result;
	List	   *schemas;
	MemoryContext oldcxt;

	recomputeNamespacePath();

	oldcxt = MemoryContextSwitchTo(context);

	result = (OverrideSearchPath *) palloc0(sizeof(OverrideSearchPath));
	schemas = list_copy(activeSearchPath);
	while (schemas && linitial_oid(schemas) != activeCreationNamespace)
	{
		if (linitial_oid(schemas) == myTempNamespace)
			result->addTemp = true;
		else
		{
			Assert(linitial_oid(schemas) == PG_CATALOG_NAMESPACE);
			result->addCatalog = true;
		}
		schemas = list_delete_first(schemas);
	}
	result->schemas = schemas;

	MemoryContextSwitchTo(oldcxt);

	return result;
}