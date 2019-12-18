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
typedef  int /*<<< orphan*/  ClientData ;

/* Variables and functions */
 int TCL_ERROR ; 
 int TCL_OK ; 
 char* Tcl_GetStringFromObj (int /*<<< orphan*/ * const,int*) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_WrongNumArgs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ * const*,char*) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static int
pltcl_quote(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[])
{
	char	   *tmp;
	const char *cp1;
	char	   *cp2;
	int			length;

	/************************************************************
	 * Check call syntax
	 ************************************************************/
	if (objc != 2)
	{
		Tcl_WrongNumArgs(interp, 1, objv, "string");
		return TCL_ERROR;
	}

	/************************************************************
	 * Allocate space for the maximum the string can
	 * grow to and initialize pointers
	 ************************************************************/
	cp1 = Tcl_GetStringFromObj(objv[1], &length);
	tmp = palloc(length * 2 + 1);
	cp2 = tmp;

	/************************************************************
	 * Walk through string and double every quote and backslash
	 ************************************************************/
	while (*cp1)
	{
		if (*cp1 == '\'')
			*cp2++ = '\'';
		else
		{
			if (*cp1 == '\\')
				*cp2++ = '\\';
		}
		*cp2++ = *cp1++;
	}

	/************************************************************
	 * Terminate the string and set it as result
	 ************************************************************/
	*cp2 = '\0';
	Tcl_SetObjResult(interp, Tcl_NewStringObj(tmp, -1));
	pfree(tmp);
	return TCL_OK;
}