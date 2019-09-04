#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int_u ;
typedef  int /*<<< orphan*/  guint32 ;
struct TYPE_6__ {TYPE_2__* drawarea; } ;
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {TYPE_1__ allocation; } ;
typedef  int GdkModifierType ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GDK_BUTTON1_MASK ; 
 int GDK_BUTTON2_MASK ; 
 int GDK_BUTTON3_MASK ; 
 int GDK_BUTTON4_MASK ; 
 int GDK_BUTTON5_MASK ; 
 char MOUSE_DRAG ; 
 scalar_t__ gtk_timeout_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ gui ; 
 int /*<<< orphan*/  gui_mch_mousehide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_mouse_moved (int,int) ; 
 int /*<<< orphan*/  gui_send_mouse_event (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modifiers_gdk2mouse (int) ; 
 scalar_t__ motion_repeat_timer ; 
 int /*<<< orphan*/  motion_repeat_timer_cb ; 

__attribute__((used)) static void
process_motion_notify(int x, int y, GdkModifierType state)
{
    int	    button;
    int_u   vim_modifiers;

    button = (state & (GDK_BUTTON1_MASK | GDK_BUTTON2_MASK |
		       GDK_BUTTON3_MASK | GDK_BUTTON4_MASK |
		       GDK_BUTTON5_MASK))
	      ? MOUSE_DRAG : ' ';

    /* If our pointer is currently hidden, then we should show it. */
    gui_mch_mousehide(FALSE);

    /* Just moving the rodent above the drawing area without any button
     * being pressed. */
    if (button != MOUSE_DRAG)
    {
	gui_mouse_moved(x, y);
	return;
    }

    /* translate modifier coding between the main engine and GTK */
    vim_modifiers = modifiers_gdk2mouse(state);

    /* inform the editor engine about the occurrence of this event */
    gui_send_mouse_event(button, x, y, FALSE, vim_modifiers);

    /*
     * Auto repeat timer handling.
     */
    if (x < 0 || y < 0
	    || x >= gui.drawarea->allocation.width
	    || y >= gui.drawarea->allocation.height)
    {

	int dx;
	int dy;
	int offshoot;
	int delay = 10;

	/* Calculate the maximal distance of the cursor from the drawing area.
	 * (offshoot can't become negative here!).
	 */
	dx = x < 0 ? -x : x - gui.drawarea->allocation.width;
	dy = y < 0 ? -y : y - gui.drawarea->allocation.height;

	offshoot = dx > dy ? dx : dy;

	/* Make a linearly decaying timer delay with a threshold of 5 at a
	 * distance of 127 pixels from the main window.
	 *
	 * One could think endlessly about the most ergonomic variant here.
	 * For example it could make sense to calculate the distance from the
	 * drags start instead...
	 *
	 * Maybe a parabolic interpolation would suite us better here too...
	 */
	if (offshoot > 127)
	{
	    /* 5 appears to be somehow near to my perceptual limits :-). */
	    delay = 5;
	}
	else
	{
	    delay = (130 * (127 - offshoot)) / 127 + 5;
	}

	/* shoot again */
	if (!motion_repeat_timer)
	    motion_repeat_timer = gtk_timeout_add((guint32)delay,
						motion_repeat_timer_cb, NULL);
    }
}