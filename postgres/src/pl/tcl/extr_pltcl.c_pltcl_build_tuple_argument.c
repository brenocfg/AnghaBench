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
typedef  int /*<<< orphan*/  Tcl_Obj ;
struct TYPE_8__ {int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; scalar_t__ attgenerated; scalar_t__ attisdropped; } ;
struct TYPE_7__ {int natts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 char* NameStr (int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Tcl_NewObj () ; 
 int /*<<< orphan*/  Tcl_NewStringObj (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UTF_BEGIN ; 
 int /*<<< orphan*/  UTF_E2U (char*) ; 
 int /*<<< orphan*/  UTF_END ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static Tcl_Obj *
pltcl_build_tuple_argument(HeapTuple tuple, TupleDesc tupdesc, bool include_generated)
{
	Tcl_Obj    *retobj = Tcl_NewObj();
	int			i;
	char	   *outputstr;
	Datum		attr;
	bool		isnull;
	char	   *attname;
	Oid			typoutput;
	bool		typisvarlena;

	for (i = 0; i < tupdesc->natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(tupdesc, i);

		/* ignore dropped attributes */
		if (att->attisdropped)
			continue;

		if (att->attgenerated)
		{
			/* don't include unless requested */
			if (!include_generated)
				continue;
		}

		/************************************************************
		 * Get the attribute name
		 ************************************************************/
		attname = NameStr(att->attname);

		/************************************************************
		 * Get the attributes value
		 ************************************************************/
		attr = heap_getattr(tuple, i + 1, tupdesc, &isnull);

		/************************************************************
		 * If there is a value, append the attribute name and the
		 * value to the list
		 *
		 * Hmmm - Null attributes will cause functions to
		 *		  crash if they don't expect them - need something
		 *		  smarter here.
		 ************************************************************/
		if (!isnull)
		{
			getTypeOutputInfo(att->atttypid,
							  &typoutput, &typisvarlena);
			outputstr = OidOutputFunctionCall(typoutput, attr);
			UTF_BEGIN;
			Tcl_ListObjAppendElement(NULL, retobj,
									 Tcl_NewStringObj(UTF_E2U(attname), -1));
			UTF_END;
			UTF_BEGIN;
			Tcl_ListObjAppendElement(NULL, retobj,
									 Tcl_NewStringObj(UTF_E2U(outputstr), -1));
			UTF_END;
			pfree(outputstr);
		}
	}

	return retobj;
}