#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ii_Unique; scalar_t__ ii_Am; int ii_NumIndexAttrs; int ii_NumIndexKeyAttrs; int* ii_IndexAttrNumbers; scalar_t__ ii_Expressions; scalar_t__ ii_Predicate; int /*<<< orphan*/ * ii_ExclusionOps; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ IndexInfo ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  equal (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * map_variable_attnos (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int*) ; 

bool
CompareIndexInfo(IndexInfo *info1, IndexInfo *info2,
				 Oid *collations1, Oid *collations2,
				 Oid *opfamilies1, Oid *opfamilies2,
				 AttrNumber *attmap, int maplen)
{
	int			i;

	if (info1->ii_Unique != info2->ii_Unique)
		return false;

	/* indexes are only equivalent if they have the same access method */
	if (info1->ii_Am != info2->ii_Am)
		return false;

	/* and same number of attributes */
	if (info1->ii_NumIndexAttrs != info2->ii_NumIndexAttrs)
		return false;

	/* and same number of key attributes */
	if (info1->ii_NumIndexKeyAttrs != info2->ii_NumIndexKeyAttrs)
		return false;

	/*
	 * and columns match through the attribute map (actual attribute numbers
	 * might differ!)  Note that this implies that index columns that are
	 * expressions appear in the same positions.  We will next compare the
	 * expressions themselves.
	 */
	for (i = 0; i < info1->ii_NumIndexAttrs; i++)
	{
		if (maplen < info2->ii_IndexAttrNumbers[i])
			elog(ERROR, "incorrect attribute map");

		/* ignore expressions at this stage */
		if ((info1->ii_IndexAttrNumbers[i] != InvalidAttrNumber) &&
			(attmap[info2->ii_IndexAttrNumbers[i] - 1] !=
			 info1->ii_IndexAttrNumbers[i]))
			return false;

		/* collation and opfamily is not valid for including columns */
		if (i >= info1->ii_NumIndexKeyAttrs)
			continue;

		if (collations1[i] != collations2[i])
			return false;
		if (opfamilies1[i] != opfamilies2[i])
			return false;
	}

	/*
	 * For expression indexes: either both are expression indexes, or neither
	 * is; if they are, make sure the expressions match.
	 */
	if ((info1->ii_Expressions != NIL) != (info2->ii_Expressions != NIL))
		return false;
	if (info1->ii_Expressions != NIL)
	{
		bool		found_whole_row;
		Node	   *mapped;

		mapped = map_variable_attnos((Node *) info2->ii_Expressions,
									 1, 0, attmap, maplen,
									 InvalidOid, &found_whole_row);
		if (found_whole_row)
		{
			/*
			 * we could throw an error here, but seems out of scope for this
			 * routine.
			 */
			return false;
		}

		if (!equal(info1->ii_Expressions, mapped))
			return false;
	}

	/* Partial index predicates must be identical, if they exist */
	if ((info1->ii_Predicate == NULL) != (info2->ii_Predicate == NULL))
		return false;
	if (info1->ii_Predicate != NULL)
	{
		bool		found_whole_row;
		Node	   *mapped;

		mapped = map_variable_attnos((Node *) info2->ii_Predicate,
									 1, 0, attmap, maplen,
									 InvalidOid, &found_whole_row);
		if (found_whole_row)
		{
			/*
			 * we could throw an error here, but seems out of scope for this
			 * routine.
			 */
			return false;
		}
		if (!equal(info1->ii_Predicate, mapped))
			return false;
	}

	/* No support currently for comparing exclusion indexes. */
	if (info1->ii_ExclusionOps != NULL || info2->ii_ExclusionOps != NULL)
		return false;

	return true;
}