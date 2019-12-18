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
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  TCL_GLOBAL_ONLY ; 
 int /*<<< orphan*/  Tcl_GetStringResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_GetVar (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcontext (char*,char*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* pstrdup (char*) ; 
 char* utf_u2e (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
throw_tcl_error(Tcl_Interp *interp, const char *proname)
{
	/*
	 * Caution is needed here because Tcl_GetVar could overwrite the
	 * interpreter result (even though it's not really supposed to), and we
	 * can't control the order of evaluation of ereport arguments. Hence, make
	 * real sure we have our own copy of the result string before invoking
	 * Tcl_GetVar.
	 */
	char	   *emsg;
	char	   *econtext;

	emsg = pstrdup(utf_u2e(Tcl_GetStringResult(interp)));
	econtext = utf_u2e(Tcl_GetVar(interp, "errorInfo", TCL_GLOBAL_ONLY));
	ereport(ERROR,
			(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
			 errmsg("%s", emsg),
			 errcontext("%s\nin PL/Tcl function \"%s\"",
						econtext, proname)));
}