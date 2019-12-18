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
typedef  int char_u ;
struct TYPE_2__ {int /*<<< orphan*/ * menubar; } ;

/* Variables and functions */
 int CAR ; 
 int CSI ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GTK_MENU_SHELL (int /*<<< orphan*/ *) ; 
 scalar_t__ KE_CSI ; 
 int KS_EXTRA ; 
 int KS_MODIFIER ; 
 int K_CSI ; 
 int K_C_END ; 
 int K_C_HOME ; 
 int K_DOWN ; 
 int K_END ; 
 int K_F10 ; 
 int K_FOCUSGAINED ; 
 int K_FOCUSLOST ; 
 int K_HOME ; 
 int K_IGNORE ; 
#define  K_K0 151 
#define  K_K1 150 
#define  K_K2 149 
#define  K_K3 148 
#define  K_K4 147 
#define  K_K5 146 
#define  K_K6 145 
#define  K_K7 144 
#define  K_K8 143 
#define  K_K9 142 
#define  K_KDIVIDE 141 
#define  K_KENTER 140 
#define  K_KMINUS 139 
#define  K_KMULTIPLY 138 
#define  K_KPLUS 137 
#define  K_KPOINT 136 
 int K_LEFT ; 
 int K_NUL ; 
 int K_RIGHT ; 
 int K_SPECIAL ; 
 int K_S_END ; 
 int K_S_HOME ; 
 int K_TEAROFF ; 
 int K_UP ; 
#define  K_XDOWN 135 
#define  K_XEND 134 
#define  K_XHOME 133 
#define  K_XLEFT 132 
#define  K_XRIGHT 131 
#define  K_XUP 130 
#define  K_ZEND 129 
#define  K_ZHOME 128 
 int MB_BYTE2LEN_CHECK (int) ; 
 int /*<<< orphan*/  MB_MAXBYTES ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_SHIFT ; 
 int MapVirtualKey (int /*<<< orphan*/ ,int) ; 
 int NUL ; 
 int TO_SPECIAL (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VK_DECIMAL ; 
 int allow_keys ; 
 int /*<<< orphan*/  garbage_collect () ; 
 int /*<<< orphan*/  gtk_menu_shell_select_first (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_make_tearoff (int*) ; 
 scalar_t__ has_mbyte ; 
 scalar_t__ last_recorded_len ; 
 scalar_t__ may_garbage_collect ; 
 int mb_ptr2char (int*) ; 
 int mod_mask ; 
 int /*<<< orphan*/  mouse_col ; 
 int /*<<< orphan*/  mouse_row ; 
 int /*<<< orphan*/  no_mapping ; 
 int old_char ; 
 int old_mod_mask ; 
 int /*<<< orphan*/  old_mouse_col ; 
 int /*<<< orphan*/  old_mouse_row ; 
 int stub1 (int*) ; 
 int /*<<< orphan*/  ui_focus_change (int) ; 
 int vgetorpeek (int /*<<< orphan*/ ) ; 
 int vpeekc () ; 
 scalar_t__ want_garbage_collect ; 

int
vgetc()
{
    int		c, c2;
#ifdef FEAT_MBYTE
    int		n;
    char_u	buf[MB_MAXBYTES + 1];
    int		i;
#endif

#ifdef FEAT_EVAL
    /* Do garbage collection when garbagecollect() was called previously and
     * we are now at the toplevel. */
    if (may_garbage_collect && want_garbage_collect)
	garbage_collect();
#endif

    /*
     * If a character was put back with vungetc, it was already processed.
     * Return it directly.
     */
    if (old_char != -1)
    {
	c = old_char;
	old_char = -1;
	mod_mask = old_mod_mask;
#ifdef FEAT_MOUSE
	mouse_row = old_mouse_row;
	mouse_col = old_mouse_col;
#endif
    }
    else
    {
      mod_mask = 0x0;
      last_recorded_len = 0;
      for (;;)			/* this is done twice if there are modifiers */
      {
	if (mod_mask)		/* no mapping after modifier has been read */
	{
	    ++no_mapping;
	    ++allow_keys;
	}
	c = vgetorpeek(TRUE);
	if (mod_mask)
	{
	    --no_mapping;
	    --allow_keys;
	}

	/* Get two extra bytes for special keys */
	if (c == K_SPECIAL
#ifdef FEAT_GUI
		|| c == CSI
#endif
	   )
	{
	    int	    save_allow_keys = allow_keys;

	    ++no_mapping;
	    allow_keys = 0;		/* make sure BS is not found */
	    c2 = vgetorpeek(TRUE);	/* no mapping for these chars */
	    c = vgetorpeek(TRUE);
	    --no_mapping;
	    allow_keys = save_allow_keys;
	    if (c2 == KS_MODIFIER)
	    {
		mod_mask = c;
		continue;
	    }
	    c = TO_SPECIAL(c2, c);

#if defined(FEAT_GUI_W32) && defined(FEAT_MENU) && defined(FEAT_TEAROFF)
	    /* Handle K_TEAROFF here, the caller of vgetc() doesn't need to
	     * know that a menu was torn off */
	    if (c == K_TEAROFF)
	    {
		char_u	name[200];
		int	i;

		/* get menu path, it ends with a <CR> */
		for (i = 0; (c = vgetorpeek(TRUE)) != '\r'; )
		{
		    name[i] = c;
		    if (i < 199)
			++i;
		}
		name[i] = NUL;
		gui_make_tearoff(name);
		continue;
	    }
#endif
#if defined(FEAT_GUI) && defined(FEAT_GUI_GTK) && defined(FEAT_MENU)
	    /* GTK: <F10> normally selects the menu, but it's passed until
	     * here to allow mapping it.  Intercept and invoke the GTK
	     * behavior if it's not mapped. */
	    if (c == K_F10 && gui.menubar != NULL)
	    {
		gtk_menu_shell_select_first(GTK_MENU_SHELL(gui.menubar), FALSE);
		continue;
	    }
#endif
#ifdef FEAT_GUI
	    /* Handle focus event here, so that the caller doesn't need to
	     * know about it.  Return K_IGNORE so that we loop once (needed if
	     * 'lazyredraw' is set). */
	    if (c == K_FOCUSGAINED || c == K_FOCUSLOST)
	    {
		ui_focus_change(c == K_FOCUSGAINED);
		c = K_IGNORE;
	    }

	    /* Translate K_CSI to CSI.  The special key is only used to avoid
	     * it being recognized as the start of a special key. */
	    if (c == K_CSI)
		c = CSI;
#endif
	}
#ifdef MSDOS
	/*
	 * If K_NUL was typed, it is replaced by K_NUL, 3 in mch_inchar().
	 * Delete the 3 here.
	 */
	else if (c == K_NUL && vpeekc() == 3)
	    (void)vgetorpeek(TRUE);
#endif

	/* a keypad or special function key was not mapped, use it like
	 * its ASCII equivalent */
	switch (c)
	{
	    case K_KPLUS:		c = '+'; break;
	    case K_KMINUS:		c = '-'; break;
	    case K_KDIVIDE:		c = '/'; break;
	    case K_KMULTIPLY:	c = '*'; break;
	    case K_KENTER:		c = CAR; break;
	    case K_KPOINT:
#ifdef WIN32
				    /* Can be either '.' or a ',', *
				     * depending on the type of keypad. */
				    c = MapVirtualKey(VK_DECIMAL, 2); break;
#else
				    c = '.'; break;
#endif
	    case K_K0:		c = '0'; break;
	    case K_K1:		c = '1'; break;
	    case K_K2:		c = '2'; break;
	    case K_K3:		c = '3'; break;
	    case K_K4:		c = '4'; break;
	    case K_K5:		c = '5'; break;
	    case K_K6:		c = '6'; break;
	    case K_K7:		c = '7'; break;
	    case K_K8:		c = '8'; break;
	    case K_K9:		c = '9'; break;

	    case K_XHOME:
	    case K_ZHOME:	if (mod_mask == MOD_MASK_SHIFT)
				{
				    c = K_S_HOME;
				    mod_mask = 0;
				}
				else if (mod_mask == MOD_MASK_CTRL)
				{
				    c = K_C_HOME;
				    mod_mask = 0;
				}
				else
				    c = K_HOME;
				break;
	    case K_XEND:
	    case K_ZEND:	if (mod_mask == MOD_MASK_SHIFT)
				{
				    c = K_S_END;
				    mod_mask = 0;
				}
				else if (mod_mask == MOD_MASK_CTRL)
				{
				    c = K_C_END;
				    mod_mask = 0;
				}
				else
				    c = K_END;
				break;

	    case K_XUP:		c = K_UP; break;
	    case K_XDOWN:	c = K_DOWN; break;
	    case K_XLEFT:	c = K_LEFT; break;
	    case K_XRIGHT:	c = K_RIGHT; break;
	}

#ifdef FEAT_MBYTE
	/* For a multi-byte character get all the bytes and return the
	 * converted character.
	 * Note: This will loop until enough bytes are received!
	 */
	if (has_mbyte && (n = MB_BYTE2LEN_CHECK(c)) > 1)
	{
	    ++no_mapping;
	    buf[0] = c;
	    for (i = 1; i < n; ++i)
	    {
		buf[i] = vgetorpeek(TRUE);
		if (buf[i] == K_SPECIAL
#ifdef FEAT_GUI
			|| buf[i] == CSI
#endif
			)
		{
		    /* Must be a K_SPECIAL - KS_SPECIAL - KE_FILLER sequence,
		     * which represents a K_SPECIAL (0x80),
		     * or a CSI - KS_EXTRA - KE_CSI sequence, which represents
		     * a CSI (0x9B),
		     * of a K_SPECIAL - KS_EXTRA - KE_CSI, which is CSI too. */
		    c = vgetorpeek(TRUE);
		    if (vgetorpeek(TRUE) == (int)KE_CSI && c == KS_EXTRA)
			buf[i] = CSI;
		}
	    }
	    --no_mapping;
	    c = (*mb_ptr2char)(buf);
	}
#endif

	break;
      }
    }

#ifdef FEAT_EVAL
    /*
     * In the main loop "may_garbage_collect" can be set to do garbage
     * collection in the first next vgetc().  It's disabled after that to
     * avoid internally used Lists and Dicts to be freed.
     */
    may_garbage_collect = FALSE;
#endif

    return c;
}