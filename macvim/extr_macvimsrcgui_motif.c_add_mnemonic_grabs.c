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
typedef  int /*<<< orphan*/ * WidgetList ;
typedef  int /*<<< orphan*/  Widget ;
typedef  char KeySym ;
typedef  int Boolean ;

/* Variables and functions */
 int False ; 
 int /*<<< orphan*/  GrabModeAsync ; 
 int /*<<< orphan*/  Mod1Mask ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XKeysymToKeycode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XStringToKeysym (char*) ; 
 int /*<<< orphan*/  XmNchildren ; 
 int /*<<< orphan*/  XmNmnemonic ; 
 int /*<<< orphan*/  XmNnumChildren ; 
 int /*<<< orphan*/  XmNrowColumnType ; 
 scalar_t__ XmWORK_AREA ; 
 scalar_t__ XtClass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtGrabKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XtIsComposite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtVaGetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ xmRowColumnWidgetClass ; 

__attribute__((used)) static void
add_mnemonic_grabs(Widget dialog, Widget w)
{
    char	    mneString[2];
    WidgetList	    children;
    int		    numChildren, i;
    Boolean	    isMenu;
    KeySym	    mnemonic = '\0';
    unsigned char   rowColType;

    if (XtIsComposite(w))
    {
	if (XtClass(w) == xmRowColumnWidgetClass)
	{
	    XtVaGetValues(w, XmNrowColumnType, &rowColType, NULL);
	    isMenu = (rowColType != (unsigned char)XmWORK_AREA);
	}
	else
	    isMenu = False;
	if (!isMenu)
	{
	    XtVaGetValues(w, XmNchildren, &children, XmNnumChildren,
							  &numChildren, NULL);
	    for (i = 0; i < numChildren; i++)
		add_mnemonic_grabs(dialog, children[i]);
	}
    }
    else
    {
	XtVaGetValues(w, XmNmnemonic, &mnemonic, NULL);
	if (mnemonic != '\0')
	{
	    mneString[0] = mnemonic;
	    mneString[1] = '\0';
	    XtGrabKey(dialog, XKeysymToKeycode(XtDisplay(dialog),
						  XStringToKeysym(mneString)),
		    Mod1Mask, True, GrabModeAsync, GrabModeAsync);
	}
    }
}