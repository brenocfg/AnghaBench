#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nargs; int /*<<< orphan*/  plan; int /*<<< orphan*/ * argtypioparams; int /*<<< orphan*/ * arginfuncs; } ;
typedef  TYPE_3__ pltcl_query_desc ;
typedef  enum options { ____Placeholder_options } options ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
typedef  int /*<<< orphan*/  Tcl_HashTable ;
typedef  int /*<<< orphan*/  Tcl_HashEntry ;
struct TYPE_8__ {TYPE_2__* prodesc; } ;
struct TYPE_6__ {int /*<<< orphan*/  fn_readonly; TYPE_1__* interp_desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  query_hash; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ClientData ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  InputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int SPI_execute_plan (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_processed ; 
 int /*<<< orphan*/  SPI_tuptable ; 
 int TCL_ERROR ; 
 int /*<<< orphan*/  TCL_EXACT ; 
 scalar_t__ TCL_OK ; 
 int /*<<< orphan*/  Tcl_AppendResult (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_FindHashEntry (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ Tcl_GetHashValue (int /*<<< orphan*/ *) ; 
 scalar_t__ Tcl_GetIndexFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ Tcl_GetIntFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int*) ; 
 char* Tcl_GetString (int /*<<< orphan*/ *) ; 
 scalar_t__ Tcl_ListObjGetElements (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int*,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_WrongNumArgs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ * const*,char*) ; 
 int /*<<< orphan*/  UTF_BEGIN ; 
 int /*<<< orphan*/  UTF_END ; 
 int /*<<< orphan*/ * UTF_U2E (char*) ; 
 scalar_t__ palloc (int) ; 
 TYPE_4__* pltcl_current_call_state ; 
 int pltcl_process_SPI_result (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltcl_subtrans_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltcl_subtrans_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltcl_subtrans_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
pltcl_SPI_execute_plan(ClientData cdata, Tcl_Interp *interp,
					   int objc, Tcl_Obj *const objv[])
{
	int			my_rc;
	int			spi_rc;
	int			i;
	int			j;
	int			optIndex;
	Tcl_HashEntry *hashent;
	pltcl_query_desc *qdesc;
	const char *nulls = NULL;
	const char *arrayname = NULL;
	Tcl_Obj    *loop_body = NULL;
	int			count = 0;
	int			callObjc;
	Tcl_Obj   **callObjv = NULL;
	Datum	   *argvalues;
	MemoryContext oldcontext = CurrentMemoryContext;
	ResourceOwner oldowner = CurrentResourceOwner;
	Tcl_HashTable *query_hash;

	enum options
	{
		OPT_ARRAY, OPT_COUNT, OPT_NULLS
	};

	static const char *options[] = {
		"-array", "-count", "-nulls", (const char *) NULL
	};

	/************************************************************
	 * Get the options and check syntax
	 ************************************************************/
	i = 1;
	while (i < objc)
	{
		if (Tcl_GetIndexFromObj(NULL, objv[i], options, NULL,
								TCL_EXACT, &optIndex) != TCL_OK)
			break;

		if (++i >= objc)
		{
			Tcl_SetObjResult(interp,
							 Tcl_NewStringObj("missing argument to -array, -count or -nulls", -1));
			return TCL_ERROR;
		}

		switch ((enum options) optIndex)
		{
			case OPT_ARRAY:
				arrayname = Tcl_GetString(objv[i++]);
				break;

			case OPT_COUNT:
				if (Tcl_GetIntFromObj(interp, objv[i++], &count) != TCL_OK)
					return TCL_ERROR;
				break;

			case OPT_NULLS:
				nulls = Tcl_GetString(objv[i++]);
				break;
		}
	}

	/************************************************************
	 * Get the prepared plan descriptor by its key
	 ************************************************************/
	if (i >= objc)
	{
		Tcl_SetObjResult(interp,
						 Tcl_NewStringObj("missing argument to -count or -array", -1));
		return TCL_ERROR;
	}

	query_hash = &pltcl_current_call_state->prodesc->interp_desc->query_hash;

	hashent = Tcl_FindHashEntry(query_hash, Tcl_GetString(objv[i]));
	if (hashent == NULL)
	{
		Tcl_AppendResult(interp, "invalid queryid '", Tcl_GetString(objv[i]), "'", NULL);
		return TCL_ERROR;
	}
	qdesc = (pltcl_query_desc *) Tcl_GetHashValue(hashent);
	i++;

	/************************************************************
	 * If a nulls string is given, check for correct length
	 ************************************************************/
	if (nulls != NULL)
	{
		if (strlen(nulls) != qdesc->nargs)
		{
			Tcl_SetObjResult(interp,
							 Tcl_NewStringObj(
											  "length of nulls string doesn't match number of arguments",
											  -1));
			return TCL_ERROR;
		}
	}

	/************************************************************
	 * If there was an argtype list on preparation, we need
	 * an argument value list now
	 ************************************************************/
	if (qdesc->nargs > 0)
	{
		if (i >= objc)
		{
			Tcl_SetObjResult(interp,
							 Tcl_NewStringObj(
											  "argument list length doesn't match number of arguments for query"
											  ,-1));
			return TCL_ERROR;
		}

		/************************************************************
		 * Split the argument values
		 ************************************************************/
		if (Tcl_ListObjGetElements(interp, objv[i++], &callObjc, &callObjv) != TCL_OK)
			return TCL_ERROR;

		/************************************************************
		 * Check that the number of arguments matches
		 ************************************************************/
		if (callObjc != qdesc->nargs)
		{
			Tcl_SetObjResult(interp,
							 Tcl_NewStringObj(
											  "argument list length doesn't match number of arguments for query"
											  ,-1));
			return TCL_ERROR;
		}
	}
	else
		callObjc = 0;

	/************************************************************
	 * Get loop body if present
	 ************************************************************/
	if (i < objc)
		loop_body = objv[i++];

	if (i != objc)
	{
		Tcl_WrongNumArgs(interp, 1, objv,
						 "?-count n? ?-array name? ?-nulls string? "
						 "query ?args? ?loop body?");
		return TCL_ERROR;
	}

	/************************************************************
	 * Execute the plan inside a sub-transaction, so we can cope with
	 * errors sanely
	 ************************************************************/

	pltcl_subtrans_begin(oldcontext, oldowner);

	PG_TRY();
	{
		/************************************************************
		 * Setup the value array for SPI_execute_plan() using
		 * the type specific input functions
		 ************************************************************/
		argvalues = (Datum *) palloc(callObjc * sizeof(Datum));

		for (j = 0; j < callObjc; j++)
		{
			if (nulls && nulls[j] == 'n')
			{
				argvalues[j] = InputFunctionCall(&qdesc->arginfuncs[j],
												 NULL,
												 qdesc->argtypioparams[j],
												 -1);
			}
			else
			{
				UTF_BEGIN;
				argvalues[j] = InputFunctionCall(&qdesc->arginfuncs[j],
												 UTF_U2E(Tcl_GetString(callObjv[j])),
												 qdesc->argtypioparams[j],
												 -1);
				UTF_END;
			}
		}

		/************************************************************
		 * Execute the plan
		 ************************************************************/
		spi_rc = SPI_execute_plan(qdesc->plan, argvalues, nulls,
								  pltcl_current_call_state->prodesc->fn_readonly,
								  count);

		my_rc = pltcl_process_SPI_result(interp,
										 arrayname,
										 loop_body,
										 spi_rc,
										 SPI_tuptable,
										 SPI_processed);

		pltcl_subtrans_commit(oldcontext, oldowner);
	}
	PG_CATCH();
	{
		pltcl_subtrans_abort(interp, oldcontext, oldowner);
		return TCL_ERROR;
	}
	PG_END_TRY();

	return my_rc;
}