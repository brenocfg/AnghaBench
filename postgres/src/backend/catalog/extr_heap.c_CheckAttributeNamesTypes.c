#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  attcollation; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; } ;
struct TYPE_6__ {int natts; } ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  CheckAttributeType (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_COLUMN ; 
 int /*<<< orphan*/  ERRCODE_TOO_MANY_COLUMNS ; 
 int /*<<< orphan*/  ERROR ; 
 int MaxHeapAttributeNumber ; 
 int /*<<< orphan*/  NIL ; 
 int NameStr (int /*<<< orphan*/ ) ; 
 char RELKIND_COMPOSITE_TYPE ; 
 char RELKIND_VIEW ; 
 int /*<<< orphan*/ * SystemAttributeByName (int) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 scalar_t__ strcmp (int,int) ; 

void
CheckAttributeNamesTypes(TupleDesc tupdesc, char relkind,
						 int flags)
{
	int			i;
	int			j;
	int			natts = tupdesc->natts;

	/* Sanity check on column count */
	if (natts < 0 || natts > MaxHeapAttributeNumber)
		ereport(ERROR,
				(errcode(ERRCODE_TOO_MANY_COLUMNS),
				 errmsg("tables can have at most %d columns",
						MaxHeapAttributeNumber)));

	/*
	 * first check for collision with system attribute names
	 *
	 * Skip this for a view or type relation, since those don't have system
	 * attributes.
	 */
	if (relkind != RELKIND_VIEW && relkind != RELKIND_COMPOSITE_TYPE)
	{
		for (i = 0; i < natts; i++)
		{
			Form_pg_attribute attr = TupleDescAttr(tupdesc, i);

			if (SystemAttributeByName(NameStr(attr->attname)) != NULL)
				ereport(ERROR,
						(errcode(ERRCODE_DUPLICATE_COLUMN),
						 errmsg("column name \"%s\" conflicts with a system column name",
								NameStr(attr->attname))));
		}
	}

	/*
	 * next check for repeated attribute names
	 */
	for (i = 1; i < natts; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (strcmp(NameStr(TupleDescAttr(tupdesc, j)->attname),
					   NameStr(TupleDescAttr(tupdesc, i)->attname)) == 0)
				ereport(ERROR,
						(errcode(ERRCODE_DUPLICATE_COLUMN),
						 errmsg("column name \"%s\" specified more than once",
								NameStr(TupleDescAttr(tupdesc, j)->attname))));
		}
	}

	/*
	 * next check the attribute types
	 */
	for (i = 0; i < natts; i++)
	{
		CheckAttributeType(NameStr(TupleDescAttr(tupdesc, i)->attname),
						   TupleDescAttr(tupdesc, i)->atttypid,
						   TupleDescAttr(tupdesc, i)->attcollation,
						   NIL, /* assume we're creating a new rowtype */
						   flags);
	}
}