#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nargs; void** argtypes; void** argtypioparams; int /*<<< orphan*/  qname; int /*<<< orphan*/ * plan; int /*<<< orphan*/ * arginfuncs; } ;
typedef  TYPE_3__ pltcl_query_desc ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
typedef  int /*<<< orphan*/  Tcl_HashTable ;
typedef  int /*<<< orphan*/  Tcl_HashEntry ;
struct TYPE_9__ {TYPE_2__* prodesc; } ;
struct TYPE_7__ {TYPE_1__* interp_desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  query_hash; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/ * volatile MemoryContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  ClientData ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 scalar_t__ SPI_keepplan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SPI_prepare (int /*<<< orphan*/ ,int,void**) ; 
 int TCL_ERROR ; 
 scalar_t__ TCL_OK ; 
 int /*<<< orphan*/ * Tcl_CreateHashEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Tcl_GetString (int /*<<< orphan*/ * const) ; 
 scalar_t__ Tcl_ListObjGetElements (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int*,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Tcl_SetHashValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_WrongNumArgs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ * const*,char*) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  UTF_BEGIN ; 
 int /*<<< orphan*/  UTF_END ; 
 int /*<<< orphan*/  UTF_U2E (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fmgr_info_cxt (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/  getTypeInputInfo (void*,void**,void**) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  parseTypeString (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int) ; 
 TYPE_5__* pltcl_current_call_state ; 
 int /*<<< orphan*/  pltcl_subtrans_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ * volatile,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltcl_subtrans_begin (int /*<<< orphan*/ * volatile,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltcl_subtrans_commit (int /*<<< orphan*/ * volatile,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,TYPE_3__*) ; 

__attribute__((used)) static int
pltcl_SPI_prepare(ClientData cdata, Tcl_Interp *interp,
				  int objc, Tcl_Obj *const objv[])
{
	volatile MemoryContext plan_cxt = NULL;
	int			nargs;
	Tcl_Obj   **argsObj;
	pltcl_query_desc *qdesc;
	int			i;
	Tcl_HashEntry *hashent;
	int			hashnew;
	Tcl_HashTable *query_hash;
	MemoryContext oldcontext = CurrentMemoryContext;
	ResourceOwner oldowner = CurrentResourceOwner;

	/************************************************************
	 * Check the call syntax
	 ************************************************************/
	if (objc != 3)
	{
		Tcl_WrongNumArgs(interp, 1, objv, "query argtypes");
		return TCL_ERROR;
	}

	/************************************************************
	 * Split the argument type list
	 ************************************************************/
	if (Tcl_ListObjGetElements(interp, objv[2], &nargs, &argsObj) != TCL_OK)
		return TCL_ERROR;

	/************************************************************
	 * Allocate the new querydesc structure
	 *
	 * struct qdesc and subsidiary data all live in plan_cxt.  Note that if the
	 * function is recompiled for whatever reason, permanent memory leaks
	 * occur.  FIXME someday.
	 ************************************************************/
	plan_cxt = AllocSetContextCreate(TopMemoryContext,
									 "PL/Tcl spi_prepare query",
									 ALLOCSET_SMALL_SIZES);
	MemoryContextSwitchTo(plan_cxt);
	qdesc = (pltcl_query_desc *) palloc0(sizeof(pltcl_query_desc));
	snprintf(qdesc->qname, sizeof(qdesc->qname), "%p", qdesc);
	qdesc->nargs = nargs;
	qdesc->argtypes = (Oid *) palloc(nargs * sizeof(Oid));
	qdesc->arginfuncs = (FmgrInfo *) palloc(nargs * sizeof(FmgrInfo));
	qdesc->argtypioparams = (Oid *) palloc(nargs * sizeof(Oid));
	MemoryContextSwitchTo(oldcontext);

	/************************************************************
	 * Execute the prepare inside a sub-transaction, so we can cope with
	 * errors sanely
	 ************************************************************/

	pltcl_subtrans_begin(oldcontext, oldowner);

	PG_TRY();
	{
		/************************************************************
		 * Resolve argument type names and then look them up by oid
		 * in the system cache, and remember the required information
		 * for input conversion.
		 ************************************************************/
		for (i = 0; i < nargs; i++)
		{
			Oid			typId,
						typInput,
						typIOParam;
			int32		typmod;

			parseTypeString(Tcl_GetString(argsObj[i]), &typId, &typmod, false);

			getTypeInputInfo(typId, &typInput, &typIOParam);

			qdesc->argtypes[i] = typId;
			fmgr_info_cxt(typInput, &(qdesc->arginfuncs[i]), plan_cxt);
			qdesc->argtypioparams[i] = typIOParam;
		}

		/************************************************************
		 * Prepare the plan and check for errors
		 ************************************************************/
		UTF_BEGIN;
		qdesc->plan = SPI_prepare(UTF_U2E(Tcl_GetString(objv[1])),
								  nargs, qdesc->argtypes);
		UTF_END;

		if (qdesc->plan == NULL)
			elog(ERROR, "SPI_prepare() failed");

		/************************************************************
		 * Save the plan into permanent memory (right now it's in the
		 * SPI procCxt, which will go away at function end).
		 ************************************************************/
		if (SPI_keepplan(qdesc->plan))
			elog(ERROR, "SPI_keepplan() failed");

		pltcl_subtrans_commit(oldcontext, oldowner);
	}
	PG_CATCH();
	{
		pltcl_subtrans_abort(interp, oldcontext, oldowner);

		MemoryContextDelete(plan_cxt);

		return TCL_ERROR;
	}
	PG_END_TRY();

	/************************************************************
	 * Insert a hashtable entry for the plan and return
	 * the key to the caller
	 ************************************************************/
	query_hash = &pltcl_current_call_state->prodesc->interp_desc->query_hash;

	hashent = Tcl_CreateHashEntry(query_hash, qdesc->qname, &hashnew);
	Tcl_SetHashValue(hashent, (ClientData) qdesc);

	/* qname is ASCII, so no need for encoding conversion */
	Tcl_SetObjResult(interp, Tcl_NewStringObj(qdesc->qname, -1));
	return TCL_OK;
}