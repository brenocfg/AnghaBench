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
typedef  int /*<<< orphan*/  char_u ;
typedef  int XtInputMask ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GO_FOOTER ; 
 int /*<<< orphan*/  GO_MENUS ; 
 int /*<<< orphan*/  GO_TOOLBAR ; 
 int /*<<< orphan*/  STRCAT (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STRCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  XmNheight ; 
 int /*<<< orphan*/  XmNwidth ; 
 int XtAppPending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtAppProcessEvent (int /*<<< orphan*/ ,int) ; 
 int XtIMAlternateInput ; 
 int /*<<< orphan*/  XtVaSetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_context ; 
 int /*<<< orphan*/  p_go ; 
 int /*<<< orphan*/  set_option_value (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vimShell ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workshopInitDone ; 
 scalar_t__ workshop_get_width_height (int*,int*) ; 

void
workshop_init()
{
    char_u	 buf[64];
    int		 is_dirty = FALSE;
    int		 width, height;
    XtInputMask	 mask;

    /*
     * Turn on MenuBar, ToolBar, and Footer.
     */
    STRCPY(buf, p_go);
    if (vim_strchr(p_go, GO_MENUS) == NULL)
    {
	STRCAT(buf, "m");
	is_dirty = TRUE;
    }
    if (vim_strchr(p_go, GO_TOOLBAR) == NULL)
    {
	STRCAT(buf, "T");
	is_dirty = TRUE;
    }
    if (vim_strchr(p_go, GO_FOOTER) == NULL)
    {
	STRCAT(buf, "F");
	is_dirty = TRUE;
    }
    if (is_dirty)
	set_option_value((char_u *)"go", 0L, buf, 0);

    /*
     * Set size from workshop_get_width_height().
     */
    width = height = 0;
    if (workshop_get_width_height(&width, &height))
    {
	XtVaSetValues(vimShell,
		XmNwidth, width,
		XmNheight, height,
		NULL);
    }

    /*
     * Now read in the initial messages from eserve.
     */
    while ((mask = XtAppPending(app_context))
	    && (mask & XtIMAlternateInput) && !workshopInitDone)
	XtAppProcessEvent(app_context, (XtInputMask)XtIMAlternateInput);
}