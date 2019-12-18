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
struct TYPE_2__ {int /*<<< orphan*/  dying; int /*<<< orphan*/ * dpy; } ;

/* Variables and functions */
 int CARDINAL ; 
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int FAIL ; 
 int OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VIM_CLASS ; 
 int /*<<< orphan*/  VIM_NAME ; 
 int /*<<< orphan*/  XtNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XtOpenDisplay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtSetLanguageProc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * app_context ; 
 int /*<<< orphan*/  cmdline_options ; 
 int /*<<< orphan*/  e_opendisp ; 
 TYPE_1__ gui ; 
 int gui_argc ; 
 int /*<<< orphan*/  gui_argv ; 
 int /*<<< orphan*/  open_app_context () ; 

int
gui_mch_init_check()
{
#ifdef FEAT_XIM
    XtSetLanguageProc(NULL, NULL, NULL);
#endif
    open_app_context();
    if (app_context != NULL)
	gui.dpy = XtOpenDisplay(app_context, 0, VIM_NAME, VIM_CLASS,
		cmdline_options, XtNumber(cmdline_options),
		CARDINAL &gui_argc, gui_argv);

    if (app_context == NULL || gui.dpy == NULL)
    {
	gui.dying = TRUE;
	EMSG(_(e_opendisp));
	return FAIL;
    }
    return OK;
}