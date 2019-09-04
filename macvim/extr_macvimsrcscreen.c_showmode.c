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

/* Variables and functions */
 char Ctrl_V ; 
 void* FALSE ; 
 int /*<<< orphan*/  HLF_CM ; 
 int INSERT ; 
 int /*<<< orphan*/  KeyTyped ; 
 int /*<<< orphan*/  MSG_PUTS_ATTR (char*,int) ; 
 char* N_ (char*) ; 
 int REPLACE_FLAG ; 
 scalar_t__ Recording ; 
 int Rows ; 
 int State ; 
 void* TRUE ; 
 scalar_t__ VIsual_active ; 
 char VIsual_mode ; 
 scalar_t__ VIsual_select ; 
 char* _ (char*) ; 
 scalar_t__ char_avail () ; 
 int /*<<< orphan*/  check_for_delay (void*) ; 
 int clear_cmdline ; 
 int cmdline_row ; 
 int /*<<< orphan*/  cursor_off () ; 
 int hl_attr (int /*<<< orphan*/ ) ; 
 void* mode_displayed ; 
 int /*<<< orphan*/  msg_clr_cmdline () ; 
 int /*<<< orphan*/  msg_clr_eos () ; 
 int msg_col ; 
 void* msg_didout ; 
 int /*<<< orphan*/  msg_pos_mode () ; 
 scalar_t__ msg_silent ; 
 int need_wait_return ; 
 scalar_t__ p_paste ; 
 scalar_t__ p_smd ; 
 void* redraw_cmdline ; 
 int /*<<< orphan*/  redrawing () ; 
 char restart_edit ; 

int
showmode()
{
    int		need_clear;
    int		length = 0;
    int		do_mode;
    int		attr;
    int		nwr_save;
#ifdef FEAT_INS_EXPAND
    int		sub_attr;
#endif

    do_mode = ((p_smd && msg_silent == 0)
	    && ((State & INSERT)
		|| restart_edit
		|| VIsual_active));
    if (do_mode || Recording)
    {
	/*
	 * Don't show mode right now, when not redrawing or inside a mapping.
	 * Call char_avail() only when we are going to show something, because
	 * it takes a bit of time.
	 */
	if (!redrawing() || (char_avail() && !KeyTyped) || msg_silent != 0)
	{
	    redraw_cmdline = TRUE;		/* show mode later */
	    return 0;
	}

	nwr_save = need_wait_return;

	/* wait a bit before overwriting an important message */
	check_for_delay(FALSE);

	/* if the cmdline is more than one line high, erase top lines */
	need_clear = clear_cmdline;
	if (clear_cmdline && cmdline_row < Rows - 1)
	    msg_clr_cmdline();			/* will reset clear_cmdline */

	/* Position on the last line in the window, column 0 */
	msg_pos_mode();
	cursor_off();
	attr = hl_attr(HLF_CM);			/* Highlight mode */
	if (do_mode)
	{
	    MSG_PUTS_ATTR("--", attr);
#if defined(FEAT_XIM)
	    if (
# if defined(FEAT_GUI_GTK) || defined(FEAT_GUI_MACVIM)
		    preedit_get_status()
# else
		    im_get_status()
# endif
	       )
# if defined(FEAT_GUI_GTK) || defined(FEAT_GUI_MACVIM)
		/* most of the time, it's not XIM being used */
		MSG_PUTS_ATTR(" IM", attr);
# else
		MSG_PUTS_ATTR(" XIM", attr);
# endif
#endif
#if defined(FEAT_HANGULIN) && defined(FEAT_GUI)
	    if (gui.in_use)
	    {
		if (hangul_input_state_get())
		    MSG_PUTS_ATTR(" \307\321\261\333", attr);   /* HANGUL */
	    }
#endif
#ifdef FEAT_INS_EXPAND
	    /* CTRL-X in Insert mode */
	    if (edit_submode != NULL && !shortmess(SHM_COMPLETIONMENU))
	    {
		/* These messages can get long, avoid a wrap in a narrow
		 * window.  Prefer showing edit_submode_extra. */
		length = (Rows - msg_row) * Columns - 3;
		if (edit_submode_extra != NULL)
		    length -= vim_strsize(edit_submode_extra);
		if (length > 0)
		{
		    if (edit_submode_pre != NULL)
			length -= vim_strsize(edit_submode_pre);
		    if (length - vim_strsize(edit_submode) > 0)
		    {
			if (edit_submode_pre != NULL)
			    msg_puts_attr(edit_submode_pre, attr);
			msg_puts_attr(edit_submode, attr);
		    }
		    if (edit_submode_extra != NULL)
		    {
			MSG_PUTS_ATTR(" ", attr);  /* add a space in between */
			if ((int)edit_submode_highl < (int)HLF_COUNT)
			    sub_attr = hl_attr(edit_submode_highl);
			else
			    sub_attr = attr;
			msg_puts_attr(edit_submode_extra, sub_attr);
		    }
		}
		length = 0;
	    }
	    else
#endif
	    {
#ifdef FEAT_VREPLACE
		if (State & VREPLACE_FLAG)
		    MSG_PUTS_ATTR(_(" VREPLACE"), attr);
		else
#endif
		    if (State & REPLACE_FLAG)
		    MSG_PUTS_ATTR(_(" REPLACE"), attr);
		else if (State & INSERT)
		{
#ifdef FEAT_RIGHTLEFT
		    if (p_ri)
			MSG_PUTS_ATTR(_(" REVERSE"), attr);
#endif
		    MSG_PUTS_ATTR(_(" INSERT"), attr);
		}
		else if (restart_edit == 'I')
		    MSG_PUTS_ATTR(_(" (insert)"), attr);
		else if (restart_edit == 'R')
		    MSG_PUTS_ATTR(_(" (replace)"), attr);
		else if (restart_edit == 'V')
		    MSG_PUTS_ATTR(_(" (vreplace)"), attr);
#ifdef FEAT_RIGHTLEFT
		if (p_hkmap)
		    MSG_PUTS_ATTR(_(" Hebrew"), attr);
# ifdef FEAT_FKMAP
		if (p_fkmap)
		    MSG_PUTS_ATTR(farsi_text_5, attr);
# endif
#endif
#ifdef FEAT_KEYMAP
		if (State & LANGMAP)
		{
# ifdef FEAT_ARABIC
		    if (curwin->w_p_arab)
			MSG_PUTS_ATTR(_(" Arabic"), attr);
		    else
# endif
			MSG_PUTS_ATTR(_(" (lang)"), attr);
		}
#endif
		if ((State & INSERT) && p_paste)
		    MSG_PUTS_ATTR(_(" (paste)"), attr);

		if (VIsual_active)
		{
		    char *p;

		    /* Don't concatenate separate words to avoid translation
		     * problems. */
		    switch ((VIsual_select ? 4 : 0)
			    + (VIsual_mode == Ctrl_V) * 2
			    + (VIsual_mode == 'V'))
		    {
			case 0:	p = N_(" VISUAL"); break;
			case 1: p = N_(" VISUAL LINE"); break;
			case 2: p = N_(" VISUAL BLOCK"); break;
			case 4: p = N_(" SELECT"); break;
			case 5: p = N_(" SELECT LINE"); break;
			default: p = N_(" SELECT BLOCK"); break;
		    }
		    MSG_PUTS_ATTR(_(p), attr);
		}
		MSG_PUTS_ATTR(" --", attr);
	    }

	    need_clear = TRUE;
	}
	if (Recording
#ifdef FEAT_INS_EXPAND
		&& edit_submode == NULL	    /* otherwise it gets too long */
#endif
		)
	{
	    MSG_PUTS_ATTR(_("recording"), attr);
	    need_clear = TRUE;
	}

	mode_displayed = TRUE;
	if (need_clear || clear_cmdline)
	    msg_clr_eos();
	msg_didout = FALSE;		/* overwrite this message */
	length = msg_col;
	msg_col = 0;
	need_wait_return = nwr_save;	/* never ask for hit-return for this */
    }
    else if (clear_cmdline && msg_silent == 0)
	/* Clear the whole command line.  Will reset "clear_cmdline". */
	msg_clr_cmdline();

#ifdef FEAT_CMDL_INFO
    /* In Visual mode the size of the selected area must be redrawn. */
    if (VIsual_active)
	clear_showcmd();

    /* If the last window has no status line, the ruler is after the mode
     * message and must be redrawn */
    if (redrawing()
# ifdef FEAT_WINDOWS
	    && lastwin->w_status_height == 0
# endif
       )
	win_redr_ruler(lastwin, TRUE);
#endif
    redraw_cmdline = FALSE;
    clear_cmdline = FALSE;

    return length;
}