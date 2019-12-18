#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ClientData ;

/* Variables and functions */
 int /*<<< orphan*/  BeginInternalSubTransaction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCurrentSubTransaction () ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 
 int TCL_ERROR ; 
 int Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_WrongNumArgs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ * const*,char*) ; 

__attribute__((used)) static int
pltcl_subtransaction(ClientData cdata, Tcl_Interp *interp,
					 int objc, Tcl_Obj *const objv[])
{
	MemoryContext oldcontext = CurrentMemoryContext;
	ResourceOwner oldowner = CurrentResourceOwner;
	int			retcode;

	if (objc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, objv, "command");
		return TCL_ERROR;
	}

	/*
	 * Note: we don't use pltcl_subtrans_begin and friends here because we
	 * don't want the error handling in pltcl_subtrans_abort.  But otherwise
	 * the processing should be about the same as in those functions.
	 */
	BeginInternalSubTransaction(NULL);
	MemoryContextSwitchTo(oldcontext);

	retcode = Tcl_EvalObjEx(interp, objv[1], 0);

	if (retcode == TCL_ERROR)
	{
		/* Rollback the subtransaction */
		RollbackAndReleaseCurrentSubTransaction();
	}
	else
	{
		/* Commit the subtransaction */
		ReleaseCurrentSubTransaction();
	}

	/* In either case, restore previous memory context and resource owner */
	MemoryContextSwitchTo(oldcontext);
	CurrentResourceOwner = oldowner;

	return retcode;
}