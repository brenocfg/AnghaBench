#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;
typedef  int /*<<< orphan*/  ClientData ;

/* Variables and functions */
 TYPE_1__* CopyErrorData () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  FreeErrorData (TYPE_1__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  SPI_rollback () ; 
 int /*<<< orphan*/  SPI_start_transaction () ; 
 int TCL_ERROR ; 
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_NewStringObj (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTF_BEGIN ; 
 int /*<<< orphan*/  UTF_E2U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTF_END ; 
 int /*<<< orphan*/  pltcl_construct_errorCode (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
pltcl_rollback(ClientData cdata, Tcl_Interp *interp,
			   int objc, Tcl_Obj *const objv[])
{
	MemoryContext oldcontext = CurrentMemoryContext;

	PG_TRY();
	{
		SPI_rollback();
		SPI_start_transaction();
	}
	PG_CATCH();
	{
		ErrorData  *edata;

		/* Save error info */
		MemoryContextSwitchTo(oldcontext);
		edata = CopyErrorData();
		FlushErrorState();

		/* Pass the error data to Tcl */
		pltcl_construct_errorCode(interp, edata);
		UTF_BEGIN;
		Tcl_SetObjResult(interp, Tcl_NewStringObj(UTF_E2U(edata->message), -1));
		UTF_END;
		FreeErrorData(edata);

		return TCL_ERROR;
	}
	PG_END_TRY();

	return TCL_OK;
}