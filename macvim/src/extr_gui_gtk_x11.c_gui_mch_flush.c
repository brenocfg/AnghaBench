#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* drawarea; int /*<<< orphan*/ * mainwin; } ;
struct TYPE_3__ {int /*<<< orphan*/ * window; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GTK_WIDGET_REALIZED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_display_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_flush () ; 
 int /*<<< orphan*/  gdk_window_process_updates (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_display (int /*<<< orphan*/ *) ; 
 TYPE_2__ gui ; 

void
gui_mch_flush(void)
{
#ifdef HAVE_GTK_MULTIHEAD
    if (gui.mainwin != NULL && GTK_WIDGET_REALIZED(gui.mainwin))
	gdk_display_sync(gtk_widget_get_display(gui.mainwin));
#else
    gdk_flush(); /* historical misnomer: calls XSync(), not XFlush() */
#endif
    /* This happens to actually do what gui_mch_flush() is supposed to do,
     * according to the comment above. */
    if (gui.drawarea != NULL && gui.drawarea->window != NULL)
	gdk_window_process_updates(gui.drawarea->window, FALSE);
}