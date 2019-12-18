#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ owned; scalar_t__ available; } ;
struct TYPE_6__ {scalar_t__ coladd; } ;
struct TYPE_7__ {int /*<<< orphan*/  vi_curswant; TYPE_1__ vi_end; int /*<<< orphan*/  vi_start; void* vi_mode; } ;
struct TYPE_9__ {void* b_visual_mode_eval; TYPE_2__ b_visual; } ;
struct TYPE_8__ {TYPE_1__ w_cursor; int /*<<< orphan*/  w_curswant; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VIsual ; 
 int /*<<< orphan*/  VIsual_active ; 
 void* VIsual_mode ; 
 int /*<<< orphan*/  adjust_cursor_eol () ; 
 int /*<<< orphan*/  clear_cmdline ; 
 int /*<<< orphan*/  clear_showcmd () ; 
 int /*<<< orphan*/  clip_auto_select () ; 
 TYPE_5__ clip_star ; 
 TYPE_4__* curbuf ; 
 TYPE_3__* curwin ; 
 scalar_t__ mode_displayed ; 
 scalar_t__ mouse_dragging ; 
 int /*<<< orphan*/  setmouse () ; 
 int /*<<< orphan*/  virtual_active () ; 

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