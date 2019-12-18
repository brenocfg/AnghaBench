#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {int attcacheoff; } ;
struct TYPE_7__ {int tdtypmod; int /*<<< orphan*/  tdtypeid; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FormData_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRIBUTE_FIXED_PART_SIZE ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 TYPE_1__* CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECORDOID ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleDesc
BuildHardcodedDescriptor(int natts, const FormData_pg_attribute *attrs)
{
	TupleDesc	result;
	MemoryContext oldcxt;
	int			i;

	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

	result = CreateTemplateTupleDesc(natts);
	result->tdtypeid = RECORDOID;	/* not right, but we don't care */
	result->tdtypmod = -1;

	for (i = 0; i < natts; i++)
	{
		memcpy(TupleDescAttr(result, i), &attrs[i], ATTRIBUTE_FIXED_PART_SIZE);
		/* make sure attcacheoff is valid */
		TupleDescAttr(result, i)->attcacheoff = -1;
	}

	/* initialize first attribute's attcacheoff, cf RelationBuildTupleDesc */
	TupleDescAttr(result, 0)->attcacheoff = 0;

	/* Note: we don't bother to set up a TupleConstr entry */

	MemoryContextSwitchTo(oldcxt);

	return result;
}