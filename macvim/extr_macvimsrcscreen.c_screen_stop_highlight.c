#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * stop; } ;
struct TYPE_7__ {scalar_t__ bg_color; scalar_t__ fg_color; } ;
struct TYPE_9__ {TYPE_2__ term; TYPE_1__ cterm; } ;
struct TYPE_10__ {int ae_attr; TYPE_3__ ae_u; } ;
typedef  TYPE_4__ attrentry_T ;

/* Variables and functions */
 int FALSE ; 
 int HL_ALL ; 
 int HL_BOLD ; 
 int HL_INVERSE ; 
 int HL_ITALIC ; 
 int HL_STANDOUT ; 
 int HL_UNDERCURL ; 
 int HL_UNDERLINE ; 
 scalar_t__ STRCMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/ * T_CZR ; 
 int /*<<< orphan*/ * T_MD ; 
 int /*<<< orphan*/ * T_ME ; 
 int /*<<< orphan*/ * T_SE ; 
 int /*<<< orphan*/ * T_UE ; 
 scalar_t__ cterm_normal_bg_color ; 
 scalar_t__ cterm_normal_fg_bold ; 
 scalar_t__ cterm_normal_fg_color ; 
 int /*<<< orphan*/  out_str (int /*<<< orphan*/ *) ; 
 int screen_attr ; 
 TYPE_4__* syn_cterm_attr2entry (int) ; 
 TYPE_4__* syn_term_attr2entry (int) ; 
 int t_colors ; 
 int /*<<< orphan*/  term_bg_color (scalar_t__) ; 
 int /*<<< orphan*/  term_fg_color (scalar_t__) ; 

void
screen_stop_highlight()
{
    int	    do_ME = FALSE;	    /* output T_ME code */

    if (screen_attr != 0
#ifdef WIN3264
			&& termcap_active
#endif
					   )
    {
#ifdef FEAT_GUI
	if (gui.in_use)
	{
	    char	buf[20];

	    /* use internal GUI code */
	    sprintf(buf, IF_EB("\033|%dH", ESC_STR "|%dH"), screen_attr);
	    OUT_STR(buf);
	}
	else
#endif
	{
	    if (screen_attr > HL_ALL)			/* special HL attr. */
	    {
		attrentry_T *aep;

		if (t_colors > 1)
		{
		    /*
		     * Assume that t_me restores the original colors!
		     */
		    aep = syn_cterm_attr2entry(screen_attr);
		    if (aep != NULL && (aep->ae_u.cterm.fg_color
						 || aep->ae_u.cterm.bg_color))
			do_ME = TRUE;
		}
		else
		{
		    aep = syn_term_attr2entry(screen_attr);
		    if (aep != NULL && aep->ae_u.term.stop != NULL)
		    {
			if (STRCMP(aep->ae_u.term.stop, T_ME) == 0)
			    do_ME = TRUE;
			else
			    out_str(aep->ae_u.term.stop);
		    }
		}
		if (aep == NULL)	    /* did ":syntax clear" */
		    screen_attr = 0;
		else
		    screen_attr = aep->ae_attr;
	    }

	    /*
	     * Often all ending-codes are equal to T_ME.  Avoid outputting the
	     * same sequence several times.
	     */
	    if (screen_attr & HL_STANDOUT)
	    {
		if (STRCMP(T_SE, T_ME) == 0)
		    do_ME = TRUE;
		else
		    out_str(T_SE);
	    }
	    if (screen_attr & (HL_UNDERLINE | HL_UNDERCURL))
	    {
		if (STRCMP(T_UE, T_ME) == 0)
		    do_ME = TRUE;
		else
		    out_str(T_UE);
	    }
	    if (screen_attr & HL_ITALIC)
	    {
		if (STRCMP(T_CZR, T_ME) == 0)
		    do_ME = TRUE;
		else
		    out_str(T_CZR);
	    }
	    if (do_ME || (screen_attr & (HL_BOLD | HL_INVERSE)))
		out_str(T_ME);

	    if (t_colors > 1)
	    {
		/* set Normal cterm colors */
		if (cterm_normal_fg_color != 0)
		    term_fg_color(cterm_normal_fg_color - 1);
		if (cterm_normal_bg_color != 0)
		    term_bg_color(cterm_normal_bg_color - 1);
		if (cterm_normal_fg_bold)
		    out_str(T_MD);
	    }
	}
    }
    screen_attr = 0;
}