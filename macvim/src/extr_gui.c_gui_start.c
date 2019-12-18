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
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {scalar_t__ in_use; scalar_t__ dofork; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_GUIENTER ; 
 int /*<<< orphan*/  EVENT_GUIFAILED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GO_FORG ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  TMODE_COOK ; 
 int /*<<< orphan*/  TMODE_RAW ; 
 int /*<<< orphan*/  T_NAME ; 
 int /*<<< orphan*/  apply_autocmds (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curbuf ; 
 int /*<<< orphan*/  cursor_on () ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ full_screen ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_attempt_start () ; 
 int /*<<< orphan*/  gui_do_fork () ; 
 scalar_t__ gui_mch_init_check () ; 
 int /*<<< orphan*/  gui_mch_update () ; 
 int /*<<< orphan*/  p_go ; 
 int /*<<< orphan*/  set_title_defaults () ; 
 int /*<<< orphan*/  settmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  termcapinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vim_strsave (int /*<<< orphan*/ ) ; 

void
gui_start()
{
    char_u	*old_term;
    static int	recursive = 0;

    old_term = vim_strsave(T_NAME);

    settmode(TMODE_COOK);		/* stop RAW mode */
    if (full_screen)
	cursor_on();			/* needed for ":gui" in .vimrc */
    full_screen = FALSE;

    ++recursive;

#ifdef MAY_FORK
    /*
     * Quit the current process and continue in the child.
     * Makes "gvim file" disconnect from the shell it was started in.
     * Don't do this when Vim was started with "-f" or the 'f' flag is present
     * in 'guioptions'.
     */
    if (gui.dofork && !vim_strchr(p_go, GO_FORG) && recursive <= 1)
    {
	gui_do_fork();
    }
    else
#endif
    {
#ifdef FEAT_GUI_GTK
	/* If there is 'f' in 'guioptions' and specify -g argument,
	 * gui_mch_init_check() was not called yet.  */
	if (gui_mch_init_check() != OK)
	    exit(1);
#endif
	gui_attempt_start();
    }

    if (!gui.in_use)			/* failed to start GUI */
    {
	/* Back to old term settings
	 *
	 * FIXME: If we got here because a child process failed and flagged to
	 * the parent to resume, and X11 is enabled with FEAT_TITLE, this will
	 * hit an X11 I/O error and do a longjmp(), leaving recursive
	 * permanently set to 1. This is probably not as big a problem as it
	 * sounds, because gui_mch_init() in both gui_x11.c and gui_gtk_x11.c
	 * return "OK" unconditionally, so it would be very difficult to
	 * actually hit this case.
	 */
	termcapinit(old_term);
	settmode(TMODE_RAW);		/* restart RAW mode */
#ifdef FEAT_TITLE
	set_title_defaults();		/* set 'title' and 'icon' again */
#endif
    }

    vim_free(old_term);

#ifdef FEAT_AUTOCMD
    /* If the GUI started successfully, trigger the GUIEnter event, otherwise
     * the GUIFailed event. */
    gui_mch_update();
    apply_autocmds(gui.in_use ? EVENT_GUIENTER : EVENT_GUIFAILED,
						   NULL, NULL, FALSE, curbuf);
#endif
    --recursive;
}