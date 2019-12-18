#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* curbuf; char* curwin; int /*<<< orphan*/  interp; } ;

/* Variables and functions */
 int /*<<< orphan*/  Tcl_UpdateLinkedVar (int /*<<< orphan*/ ,char*) ; 
 int VARNAME_SIZE ; 
 char* VAR_CURBUF ; 
 char* VAR_CURWIN ; 
 char* VAR_LBASE ; 
 char* VAR_RANGE1 ; 
 char* VAR_RANGE2 ; 
 char* VAR_RANGE3 ; 
 int /*<<< orphan*/  curbuf ; 
 int /*<<< orphan*/  curwin ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* tclgetbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* tclgetwindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ tclinfo ; 

__attribute__((used)) static void
tclupdatevars()
{
    char varname[VARNAME_SIZE];	/* must be writeable */
    char *name;

    strcpy(varname, VAR_RANGE1);
    Tcl_UpdateLinkedVar(tclinfo.interp, varname);
    strcpy(varname, VAR_RANGE2);
    Tcl_UpdateLinkedVar(tclinfo.interp, varname);
    strcpy(varname, VAR_RANGE3);
    Tcl_UpdateLinkedVar(tclinfo.interp, varname);

    strcpy(varname, VAR_LBASE);
    Tcl_UpdateLinkedVar(tclinfo.interp, varname);

    name = tclgetbuffer(tclinfo.interp, curbuf);
    strcpy(tclinfo.curbuf, name);
    strcpy(varname, VAR_CURBUF);
    Tcl_UpdateLinkedVar(tclinfo.interp, varname);

    name = tclgetwindow(tclinfo.interp, curwin);
    strcpy(tclinfo.curwin, name);
    strcpy(varname, VAR_CURWIN);
    Tcl_UpdateLinkedVar(tclinfo.interp, varname);
}