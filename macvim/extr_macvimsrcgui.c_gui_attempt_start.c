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
struct TYPE_2__ {int starting; } ;

/* Variables and functions */
 int TRUE ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  termcapinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gui_attempt_start()
{
    static int recursive = 0;

    ++recursive;
    gui.starting = TRUE;

#ifdef FEAT_GUI_GTK
    gui.event_time = GDK_CURRENT_TIME;
#endif

    termcapinit((char_u *)"builtin_gui");
    gui.starting = recursive - 1;

#if defined(FEAT_GUI_GTK) || defined(FEAT_GUI_X11)
    if (gui.in_use)
    {
# ifdef FEAT_EVAL
	Window	x11_window;
	Display	*x11_display;

	if (gui_get_x11_windis(&x11_window, &x11_display) == OK)
	    set_vim_var_nr(VV_WINDOWID, (long)x11_window);
# endif

	/* Display error messages in a dialog now. */
	display_errors();
    }
#endif
    --recursive;
}