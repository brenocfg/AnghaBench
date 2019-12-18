#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TypeFuncClass ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_10__ {int /*<<< orphan*/  attname; } ;
struct TYPE_9__ {int natts; int tdtypmod; int /*<<< orphan*/  tdtypeid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 TYPE_1__* CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  RECORDOID ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 scalar_t__ TYPEFUNC_RECORD ; 
 scalar_t__ TYPEFUNC_SCALAR ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TupleDescInitEntry (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ get_type_func_class (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_nth (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* lookup_rowtype_tupdesc_copy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char*) ; 
 char* strVal (int /*<<< orphan*/ ) ; 

TupleDesc
TypeGetTupleDesc(Oid typeoid, List *colaliases)
{
	Oid			base_typeoid;
	TypeFuncClass functypclass = get_type_func_class(typeoid, &base_typeoid);
	TupleDesc	tupdesc = NULL;

	/*
	 * Build a suitable tupledesc representing the output rows.  We
	 * intentionally do not support TYPEFUNC_COMPOSITE_DOMAIN here, as it's
	 * unlikely that legacy callers of this obsolete function would be
	 * prepared to apply domain constraints.
	 */
	if (functypclass == TYPEFUNC_COMPOSITE)
	{
		/* Composite data type, e.g. a table's row type */
		tupdesc = lookup_rowtype_tupdesc_copy(base_typeoid, -1);

		if (colaliases != NIL)
		{
			int			natts = tupdesc->natts;
			int			varattno;

			/* does the list length match the number of attributes? */
			if (list_length(colaliases) != natts)
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("number of aliases does not match number of columns")));

			/* OK, use the aliases instead */
			for (varattno = 0; varattno < natts; varattno++)
			{
				char	   *label = strVal(list_nth(colaliases, varattno));
				Form_pg_attribute attr = TupleDescAttr(tupdesc, varattno);

				if (label != NULL)
					namestrcpy(&(attr->attname), label);
			}

			/* The tuple type is now an anonymous record type */
			tupdesc->tdtypeid = RECORDOID;
			tupdesc->tdtypmod = -1;
		}
	}
	else if (functypclass == TYPEFUNC_SCALAR)
	{
		/* Base data type, i.e. scalar */
		char	   *attname;

		/* the alias list is required for base types */
		if (colaliases == NIL)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("no column alias was provided")));

		/* the alias list length must be 1 */
		if (list_length(colaliases) != 1)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("number of aliases does not match number of columns")));

		/* OK, get the column alias */
		attname = strVal(linitial(colaliases));

		tupdesc = CreateTemplateTupleDesc(1);
		TupleDescInitEntry(tupdesc,
						   (AttrNumber) 1,
						   attname,
						   typeoid,
						   -1,
						   0);
	}
	else if (functypclass == TYPEFUNC_RECORD)
	{
		/* XXX can't support this because typmod wasn't passed in ... */
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("could not determine row description for function returning record")));
	}
	else
	{
		/* crummy error message, but parser should have caught this */
		elog(ERROR, "function in FROM has unsupported return type");
	}

	return tupdesc;
}