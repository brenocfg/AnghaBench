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
typedef  scalar_t__ sattr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int Columns ; 
 int* LineOffset ; 
 int Rows ; 
 scalar_t__* ScreenAttrs ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  can_clear (int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_undraw_cursor () ; 
 int /*<<< orphan*/  screen_del_lines (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_fill (int,int,int,int,char,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msg_scroll_up()
{
#ifdef FEAT_GUI
    /* Remove the cursor before scrolling, ScreenLines[] is going
     * to become invalid. */
    if (gui.in_use)
	gui_undraw_cursor();
#endif
    /* scrolling up always works */
    screen_del_lines(0, 0, 1, (int)Rows, TRUE, NULL);

    if (!can_clear((char_u *)" "))
    {
	/* Scrolling up doesn't result in the right background.  Set the
	 * background here.  It's not efficient, but avoids that we have to do
	 * it all over the code. */
	screen_fill((int)Rows - 1, (int)Rows, 0, (int)Columns, ' ', ' ', 0);

	/* Also clear the last char of the last but one line if it was not
	 * cleared before to avoid a scroll-up. */
	if (ScreenAttrs[LineOffset[Rows - 2] + Columns - 1] == (sattr_T)-1)
	    screen_fill((int)Rows - 2, (int)Rows - 1,
				 (int)Columns - 1, (int)Columns, ' ', ' ', 0);
    }
}