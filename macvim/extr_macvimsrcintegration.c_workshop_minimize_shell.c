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
typedef  int /*<<< orphan*/ * Widget ;

/* Variables and functions */
 scalar_t__ True ; 
 int /*<<< orphan*/  XIconifyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XScreenNumberOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmNiconic ; 
 int /*<<< orphan*/  XtDisplay (int /*<<< orphan*/ *) ; 
 scalar_t__ XtIsObject (int /*<<< orphan*/ *) ; 
 scalar_t__ XtIsRealized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtVaSetValues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ isMapped (int /*<<< orphan*/ *) ; 

void
workshop_minimize_shell(Widget shell)
{
	if (shell != NULL &&
	    XtIsObject(shell) &&
	    XtIsRealized(shell) == True) {
		if (isMapped(shell) == True) {
			XIconifyWindow(XtDisplay(shell), XtWindow(shell),
			       XScreenNumberOfScreen(XtScreen(shell)));
		}
		XtVaSetValues(shell,
			      XmNiconic, True,
			      NULL);
	}
}