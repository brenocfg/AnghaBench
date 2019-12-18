#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_4__ {TYPE_1__* fcinfo; } ;
struct TYPE_3__ {int nargs; } ;
typedef  TYPE_1__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  ClientData ;

/* Variables and functions */
 int /*<<< orphan*/  PG_ARGISNULL (int) ; 
 int TCL_ERROR ; 
 scalar_t__ TCL_OK ; 
 scalar_t__ Tcl_GetIntFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int*) ; 
 int /*<<< orphan*/  Tcl_NewBooleanObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_WrongNumArgs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ * const*,char*) ; 
 TYPE_2__* pltcl_current_call_state ; 

__attribute__((used)) static int
pltcl_argisnull(ClientData cdata, Tcl_Interp *interp,
				int objc, Tcl_Obj *const objv[])
{
	int			argno;
	FunctionCallInfo fcinfo = pltcl_current_call_state->fcinfo;

	/************************************************************
	 * Check call syntax
	 ************************************************************/
	if (objc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, objv, "argno");
		return TCL_ERROR;
	}

	/************************************************************
	 * Check that we're called as a normal function
	 ************************************************************/
	if (fcinfo == NULL)
	{
		Tcl_SetObjResult(interp,
						 Tcl_NewStringObj("argisnull cannot be used in triggers", -1));
		return TCL_ERROR;
	}

	/************************************************************
	 * Get the argument number
	 ************************************************************/
	if (Tcl_GetIntFromObj(interp, objv[1], &argno) != TCL_OK)
		return TCL_ERROR;

	/************************************************************
	 * Check that the argno is valid
	 ************************************************************/
	argno--;
	if (argno < 0 || argno >= fcinfo->nargs)
	{
		Tcl_SetObjResult(interp,
						 Tcl_NewStringObj("argno out of range", -1));
		return TCL_ERROR;
	}

	/************************************************************
	 * Get the requested NULL state
	 ************************************************************/
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(PG_ARGISNULL(argno)));
	return TCL_OK;
}