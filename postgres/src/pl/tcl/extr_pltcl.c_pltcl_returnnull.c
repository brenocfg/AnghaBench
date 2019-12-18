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
struct TYPE_3__ {int isnull; } ;
typedef  TYPE_1__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  ClientData ;

/* Variables and functions */
 int TCL_ERROR ; 
 int TCL_RETURN ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_WrongNumArgs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ * const*,char*) ; 
 TYPE_2__* pltcl_current_call_state ; 

__attribute__((used)) static int
pltcl_returnnull(ClientData cdata, Tcl_Interp *interp,
				 int objc, Tcl_Obj *const objv[])
{
	FunctionCallInfo fcinfo = pltcl_current_call_state->fcinfo;

	/************************************************************
	 * Check call syntax
	 ************************************************************/
	if (objc != 1)
	{
		Tcl_WrongNumArgs(interp, 1, objv, "");
		return TCL_ERROR;
	}

	/************************************************************
	 * Check that we're called as a normal function
	 ************************************************************/
	if (fcinfo == NULL)
	{
		Tcl_SetObjResult(interp,
						 Tcl_NewStringObj("return_null cannot be used in triggers", -1));
		return TCL_ERROR;
	}

	/************************************************************
	 * Set the NULL return flag and cause Tcl to return from the
	 * procedure.
	 ************************************************************/
	fcinfo->isnull = true;

	return TCL_RETURN;
}