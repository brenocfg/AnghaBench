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
struct TYPE_4__ {int /*<<< orphan*/  vi_curswant; int /*<<< orphan*/  vi_end; int /*<<< orphan*/  vi_start; int /*<<< orphan*/  vi_mode; } ;
struct TYPE_6__ {TYPE_1__ b_visual; } ;
struct TYPE_5__ {int /*<<< orphan*/  w_curswant; int /*<<< orphan*/  w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VIsual ; 
 int /*<<< orphan*/  VIsual_active ; 
 int /*<<< orphan*/  VIsual_mode ; 
 int /*<<< orphan*/  adjust_cursor_eol () ; 
 int /*<<< orphan*/  clear_cmdline ; 
 TYPE_3__* curbuf ; 
 TYPE_2__* curwin ; 
 scalar_t__ mode_displayed ; 

void
end_visual_mode()
{
#ifdef FEAT_CLIPBOARD
    /*
     * If we are using the clipboard, then remember what was selected in case
     * we need to paste it somewhere while we still own the selection.
     * Only do this when the clipboard is already owned.  Don't want to grab
     * the selection when hitting ESC.
     */
    if (clip_star.available && clip_star.owned)
	clip_auto_select();
#endif

    VIsual_active = FALSE;
#ifdef FEAT_MOUSE
    setmouse();
    mouse_dragging = 0;
#endif

    /* Save the current VIsual area for '< and '> marks, and "gv" */
    curbuf->b_visual.vi_mode = VIsual_mode;
    curbuf->b_visual.vi_start = VIsual;
    curbuf->b_visual.vi_end = curwin->w_cursor;
    curbuf->b_visual.vi_curswant = curwin->w_curswant;
#ifdef FEAT_EVAL
    curbuf->b_visual_mode_eval = VIsual_mode;
#endif
#ifdef FEAT_VIRTUALEDIT
    if (!virtual_active())
	curwin->w_cursor.coladd = 0;
#endif

    if (mode_displayed)
	clear_cmdline = TRUE;		/* unshow visual mode later */
#ifdef FEAT_CMDL_INFO
    else
	clear_showcmd();
#endif

    adjust_cursor_eol();
}