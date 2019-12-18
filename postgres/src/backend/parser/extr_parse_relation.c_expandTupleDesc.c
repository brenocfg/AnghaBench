#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int location; } ;
typedef  TYPE_1__ Var ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_16__ {int /*<<< orphan*/  colnames; } ;
struct TYPE_15__ {int /*<<< orphan*/  attcollation; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; scalar_t__ attisdropped; } ;
struct TYPE_14__ {int natts; } ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__ Alias ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  InvalidOid ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lfirst (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_nth_cell (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* makeNullConst (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeString (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeVar (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 
 char* strVal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expandTupleDesc(TupleDesc tupdesc, Alias *eref, int count, int offset,
				int rtindex, int sublevels_up,
				int location, bool include_dropped,
				List **colnames, List **colvars)
{
	ListCell   *aliascell;
	int			varattno;

	aliascell = (offset < list_length(eref->colnames)) ?
		list_nth_cell(eref->colnames, offset) : NULL;

	Assert(count <= tupdesc->natts);
	for (varattno = 0; varattno < count; varattno++)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, varattno);

		if (attr->attisdropped)
		{
			if (include_dropped)
			{
				if (colnames)
					*colnames = lappend(*colnames, makeString(pstrdup("")));
				if (colvars)
				{
					/*
					 * can't use atttypid here, but it doesn't really matter
					 * what type the Const claims to be.
					 */
					*colvars = lappend(*colvars,
									   makeNullConst(INT4OID, -1, InvalidOid));
				}
			}
			if (aliascell)
				aliascell = lnext(eref->colnames, aliascell);
			continue;
		}

		if (colnames)
		{
			char	   *label;

			if (aliascell)
			{
				label = strVal(lfirst(aliascell));
				aliascell = lnext(eref->colnames, aliascell);
			}
			else
			{
				/* If we run out of aliases, use the underlying name */
				label = NameStr(attr->attname);
			}
			*colnames = lappend(*colnames, makeString(pstrdup(label)));
		}

		if (colvars)
		{
			Var		   *varnode;

			varnode = makeVar(rtindex, varattno + offset + 1,
							  attr->atttypid, attr->atttypmod,
							  attr->attcollation,
							  sublevels_up);
			varnode->location = location;

			*colvars = lappend(*colvars, varnode);
		}
	}
}