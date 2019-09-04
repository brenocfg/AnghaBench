#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  w_buffer; struct TYPE_7__* w_next; } ;
typedef  TYPE_1__ win_T ;
struct TYPE_8__ {scalar_t__ tp_topframe; struct TYPE_8__* tp_next; TYPE_1__* tp_firstwin; TYPE_1__* tp_curwin; } ;
typedef  TYPE_2__ tabpage_T ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int Columns ; 
 void* FALSE ; 
 int /*<<< orphan*/  HLF_TP ; 
 int /*<<< orphan*/  HLF_TPF ; 
 int /*<<< orphan*/  HLF_TPS ; 
 int /*<<< orphan*/  MAXPATHL ; 
 int /*<<< orphan*/ * NameBuff ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int* TabPageIdxs ; 
 scalar_t__ bufIsChanged (int /*<<< orphan*/ ) ; 
 TYPE_2__* curtab ; 
 TYPE_1__* curwin ; 
 TYPE_2__* first_tabpage ; 
 TYPE_1__* firstwin ; 
 int /*<<< orphan*/  get_trans_bufname (int /*<<< orphan*/ ) ; 
 int hl_attr (int /*<<< orphan*/ ) ; 
 void* redraw_tabline ; 
 int /*<<< orphan*/  screen_fill (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  screen_putchar (char,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  screen_puts_len (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  shorten_dir (int /*<<< orphan*/ *) ; 
 int t_colors ; 
 int tabline_height () ; 
 scalar_t__ topframe ; 
 int /*<<< orphan*/  vim_snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int vim_strsize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
draw_tabline()
{
    int		tabcount = 0;
    tabpage_T	*tp;
    int		tabwidth;
    int		col = 0;
    int		scol = 0;
    int		attr;
    win_T	*wp;
    win_T	*cwp;
    int		wincount;
    int		modified;
    int		c;
    int		len;
    int		attr_sel = hl_attr(HLF_TPS);
    int		attr_nosel = hl_attr(HLF_TP);
    int		attr_fill = hl_attr(HLF_TPF);
    char_u	*p;
    int		room;
    int		use_sep_chars = (t_colors < 8
#ifdef FEAT_GUI
					    && !gui.in_use
#endif
					    );

    redraw_tabline = FALSE;

#ifdef FEAT_GUI_TABLINE
    /* Take care of a GUI tabline. */
    if (gui_use_tabline())
    {
	gui_update_tabline();
	return;
    }
#endif

    if (tabline_height() < 1)
	return;

#if defined(FEAT_STL_OPT)

    /* Init TabPageIdxs[] to zero: Clicking outside of tabs has no effect. */
    for (scol = 0; scol < Columns; ++scol)
	TabPageIdxs[scol] = 0;

    /* Use the 'tabline' option if it's set. */
    if (*p_tal != NUL)
    {
	int	save_called_emsg = called_emsg;

	/* Check for an error.  If there is one we would loop in redrawing the
	 * screen.  Avoid that by making 'tabline' empty. */
	called_emsg = FALSE;
	win_redr_custom(NULL, FALSE);
	if (called_emsg)
	    set_string_option_direct((char_u *)"tabline", -1,
					   (char_u *)"", OPT_FREE, SID_ERROR);
	called_emsg |= save_called_emsg;
    }
    else
#endif
    {
	for (tp = first_tabpage; tp != NULL; tp = tp->tp_next)
	    ++tabcount;

	tabwidth = (Columns - 1 + tabcount / 2) / tabcount;
	if (tabwidth < 6)
	    tabwidth = 6;

	attr = attr_nosel;
	tabcount = 0;
	scol = 0;
	for (tp = first_tabpage; tp != NULL && col < Columns - 4;
							     tp = tp->tp_next)
	{
	    scol = col;

	    if (tp->tp_topframe == topframe)
		attr = attr_sel;
	    if (use_sep_chars && col > 0)
		screen_putchar('|', 0, col++, attr);

	    if (tp->tp_topframe != topframe)
		attr = attr_nosel;

	    screen_putchar(' ', 0, col++, attr);

	    if (tp == curtab)
	    {
		cwp = curwin;
		wp = firstwin;
	    }
	    else
	    {
		cwp = tp->tp_curwin;
		wp = tp->tp_firstwin;
	    }

	    modified = FALSE;
	    for (wincount = 0; wp != NULL; wp = wp->w_next, ++wincount)
		if (bufIsChanged(wp->w_buffer))
		    modified = TRUE;
	    if (modified || wincount > 1)
	    {
		if (wincount > 1)
		{
		    vim_snprintf((char *)NameBuff, MAXPATHL, "%d", wincount);
		    len = (int)STRLEN(NameBuff);
		    if (col + len >= Columns - 3)
			break;
		    screen_puts_len(NameBuff, len, 0, col,
#if defined(FEAT_SYN_HL)
					   hl_combine_attr(attr, hl_attr(HLF_T))
#else
					   attr
#endif
					       );
		    col += len;
		}
		if (modified)
		    screen_puts_len((char_u *)"+", 1, 0, col++, attr);
		screen_putchar(' ', 0, col++, attr);
	    }

	    room = scol - col + tabwidth - 1;
	    if (room > 0)
	    {
		/* Get buffer name in NameBuff[] */
		get_trans_bufname(cwp->w_buffer);
		shorten_dir(NameBuff);
		len = vim_strsize(NameBuff);
		p = NameBuff;
#ifdef FEAT_MBYTE
		if (has_mbyte)
		    while (len > room)
		    {
			len -= ptr2cells(p);
			mb_ptr_adv(p);
		    }
		else
#endif
		    if (len > room)
		{
		    p += len - room;
		    len = room;
		}
		if (len > Columns - col - 1)
		    len = Columns - col - 1;

		screen_puts_len(p, (int)STRLEN(p), 0, col, attr);
		col += len;
	    }
	    screen_putchar(' ', 0, col++, attr);

	    /* Store the tab page number in TabPageIdxs[], so that
	     * jump_to_mouse() knows where each one is. */
	    ++tabcount;
	    while (scol < col)
		TabPageIdxs[scol++] = tabcount;
	}

	if (use_sep_chars)
	    c = '_';
	else
	    c = ' ';
	screen_fill(0, 1, col, (int)Columns, c, c, attr_fill);

	/* Put an "X" for closing the current tab if there are several. */
	if (first_tabpage->tp_next != NULL)
	{
	    screen_putchar('X', 0, (int)Columns - 1, attr_nosel);
	    TabPageIdxs[Columns - 1] = -999;
	}
    }

    /* Reset the flag here again, in case evaluating 'tabline' causes it to be
     * set. */
    redraw_tabline = FALSE;
}