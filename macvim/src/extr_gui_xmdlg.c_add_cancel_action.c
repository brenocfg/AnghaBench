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
typedef  int /*<<< orphan*/  XtCallbackProc ;
typedef  int /*<<< orphan*/  Widget ;
typedef  int /*<<< orphan*/  Display ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XmAddProtocolCallback (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  XmDO_NOTHING ; 
 scalar_t__ XmInternAtom (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmNdeleteResponse ; 
 int /*<<< orphan*/ * XtDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtVaSetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_cancel_action(Widget shell, XtCallbackProc close_callback, void *arg)
{
    static Atom wmp_atom = 0;
    static Atom dw_atom = 0;
    Display *display = XtDisplay(shell);

    /* deactivate the built-in delete response of killing the application */
    XtVaSetValues(shell, XmNdeleteResponse, XmDO_NOTHING, NULL);

    /* add a delete window protocol callback instead */
    if (!dw_atom)
    {
	wmp_atom = XmInternAtom(display, "WM_PROTOCOLS", True);
	dw_atom = XmInternAtom(display, "WM_DELETE_WINDOW", True);
    }
    XmAddProtocolCallback(shell, wmp_atom, dw_atom, close_callback, arg);
}