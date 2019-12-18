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
typedef  int /*<<< orphan*/  guint32 ;
typedef  scalar_t__ guint ;
typedef  scalar_t__ gint ;
struct TYPE_2__ {int in_focus; } ;

/* Variables and functions */
 int FAIL ; 
 int FALSE ; 
 int /*<<< orphan*/  GDK_INPUT_READ ; 
 int OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fd_from_sniff ; 
 int /*<<< orphan*/  g_main_context_iteration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gdk_input_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_input_remove (scalar_t__) ; 
 scalar_t__ gtk_timeout_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gtk_timeout_remove (scalar_t__) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_mch_start_blink () ; 
 int /*<<< orphan*/  gui_mch_stop_blink () ; 
 int /*<<< orphan*/  gui_mch_update () ; 
 scalar_t__ input_available () ; 
 int /*<<< orphan*/  input_timer_cb ; 
 int /*<<< orphan*/  netbeans_parse_messages () ; 
 int /*<<< orphan*/  sniff_request_cb ; 
 scalar_t__ want_sniff_request ; 

int
gui_mch_wait_for_chars(long wtime)
{
    int focus;
    guint timer;
    static int timed_out;
#ifdef FEAT_SNIFF
    static int	sniff_on = 0;
    static gint	sniff_input_id = 0;
#endif

#ifdef FEAT_SNIFF
    if (sniff_on && !want_sniff_request)
    {
	if (sniff_input_id)
	    gdk_input_remove(sniff_input_id);
	sniff_on = 0;
    }
    else if (!sniff_on && want_sniff_request)
    {
	/* Add fd_from_sniff to watch for available data in main loop. */
	sniff_input_id = gdk_input_add(fd_from_sniff,
			       GDK_INPUT_READ, sniff_request_cb, NULL);
	sniff_on = 1;
    }
#endif

    timed_out = FALSE;

    /* this timeout makes sure that we will return if no characters arrived in
     * time */

    if (wtime > 0)
	timer = gtk_timeout_add((guint32)wtime, input_timer_cb, &timed_out);
    else
	timer = 0;

    focus = gui.in_focus;

    do
    {
	/* Stop or start blinking when focus changes */
	if (gui.in_focus != focus)
	{
	    if (gui.in_focus)
		gui_mch_start_blink();
	    else
		gui_mch_stop_blink();
	    focus = gui.in_focus;
	}

#if defined(FEAT_NETBEANS_INTG)
	/* Process any queued netbeans messages. */
	netbeans_parse_messages();
#endif

	/*
	 * Loop in GTK+ processing  until a timeout or input occurs.
	 * Skip this if input is available anyway (can happen in rare
	 * situations, sort of race condition).
	 */
	if (!input_available())
	    g_main_context_iteration(NULL, TRUE);

	/* Got char, return immediately */
	if (input_available())
	{
	    if (timer != 0 && !timed_out)
		gtk_timeout_remove(timer);
	    return OK;
	}
    } while (wtime < 0 || !timed_out);

    /*
     * Flush all eventually pending (drawing) events.
     */
    gui_mch_update();

    return FAIL;
}