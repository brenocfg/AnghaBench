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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  xterm_conflict_mouse ; 

void
check_mouse_termcode()
{
    xterm_conflict_mouse = FALSE;

# ifdef FEAT_MOUSE_XTERM
    if (use_xterm_mouse()
# ifdef FEAT_MOUSE_URXVT
	    && use_xterm_mouse() != 3
# endif
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
    {
	set_mouse_termcode(KS_MOUSE, (char_u *)(term_is_8bit(T_NAME)
		    ? IF_EB("\233M", CSI_STR "M")
		    : IF_EB("\033[M", ESC_STR "[M")));
	if (*p_mouse != NUL)
	{
	    /* force mouse off and maybe on to send possibly new mouse
	     * activation sequence to the xterm, with(out) drag tracing. */
	    mch_setmouse(FALSE);
	    setmouse();
	}
    }
    else
	del_mouse_termcode(KS_MOUSE);
# endif

# ifdef FEAT_MOUSE_GPM
    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_MOUSE, (char_u *)IF_EB("\033MG", ESC_STR "MG"));
# endif

# ifdef FEAT_SYSMOUSE
    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_MOUSE, (char_u *)IF_EB("\033MS", ESC_STR "MS"));
# endif

# ifdef FEAT_MOUSE_JSB
    /* There is no conflict, but it was disabled for xterm before. */
    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_JSBTERM_MOUSE,
			       (char_u *)IF_EB("\033[0~zw", ESC_STR "[0~zw"));
    else
	del_mouse_termcode(KS_JSBTERM_MOUSE);
# endif

# ifdef FEAT_MOUSE_NET
    /* There is no conflict, but one may type "ESC }" from Insert mode.  Don't
     * define it in the GUI or when using an xterm. */
    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_NETTERM_MOUSE,
				       (char_u *)IF_EB("\033}", ESC_STR "}"));
    else
	del_mouse_termcode(KS_NETTERM_MOUSE);
# endif

# ifdef FEAT_MOUSE_DEC
    /* Conflicts with xterm mouse: "\033[" and "\033[M".
     * Also conflicts with the xterm termresponse, skip this if it was
     * requested already. */
    if (!use_xterm_mouse()
#  ifdef FEAT_TERMRESPONSE
	    && !did_request_esc_sequence()
#  endif
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
    {
	set_mouse_termcode(KS_DEC_MOUSE, (char_u *)(term_is_8bit(T_NAME)
		     ? IF_EB("\233", CSI_STR) : IF_EB("\033[", ESC_STR "[")));
	xterm_conflict_mouse = TRUE;
    }
    else
	del_mouse_termcode(KS_DEC_MOUSE);
# endif
# ifdef FEAT_MOUSE_PTERM
    /* same as the dec mouse */
    if (!use_xterm_mouse()
#  ifdef FEAT_TERMRESPONSE
	    && !did_request_esc_sequence()
#  endif
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
    {
	set_mouse_termcode(KS_PTERM_MOUSE,
				      (char_u *) IF_EB("\033[", ESC_STR "["));
	xterm_conflict_mouse = TRUE;
    }
    else
	del_mouse_termcode(KS_PTERM_MOUSE);
# endif
# ifdef FEAT_MOUSE_URXVT
    /* same as the dec mouse */
    if (use_xterm_mouse() == 3
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
    {
	set_mouse_termcode(KS_URXVT_MOUSE, (char_u *)(term_is_8bit(T_NAME)
		    ? IF_EB("\233", CSI_STR)
		    : IF_EB("\033[", ESC_STR "[")));

	if (*p_mouse != NUL)
	{
	    mch_setmouse(FALSE);
	    setmouse();
	}
	/* It's OK to request the xterm version for uxterm. */
	resume_get_esc_sequence();
    }
    else
	del_mouse_termcode(KS_URXVT_MOUSE);
# endif
# ifdef FEAT_MOUSE_SGR
    /* There is no conflict with xterm mouse */
    if (use_xterm_mouse() == 4
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
    {
	set_mouse_termcode(KS_SGR_MOUSE, (char_u *)(term_is_8bit(T_NAME)
		    ? IF_EB("\233<", CSI_STR "<")
		    : IF_EB("\033[<", ESC_STR "[<")));

	if (*p_mouse != NUL)
	{
	    mch_setmouse(FALSE);
	    setmouse();
	}
    }
    else
	del_mouse_termcode(KS_SGR_MOUSE);
# endif
}