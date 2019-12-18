#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char char_u ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int b_p_ro; int /*<<< orphan*/ * b_ffname; int /*<<< orphan*/ * b_fname; int /*<<< orphan*/  b_p_ma; } ;

/* Variables and functions */
 int Columns ; 
 void* FALSE ; 
 int IOSIZE ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  OPT_FREE ; 
 int /*<<< orphan*/  SID_ERROR ; 
 int SPACE_FOR_ARGNR ; 
 int SPACE_FOR_DIR ; 
 size_t SPACE_FOR_FNAME ; 
 int STL_IN_ICON ; 
 int STL_IN_TITLE ; 
 int /*<<< orphan*/  STRCAT (char*,char*) ; 
 int /*<<< orphan*/  STRCPY (char*,char*) ; 
 scalar_t__ STRLEN (char*) ; 
 void* TRUE ; 
 scalar_t__ _ (char*) ; 
 int /*<<< orphan*/  append_arg_number (int /*<<< orphan*/ ,char*,int,void*) ; 
 int bufIsChanged (TYPE_1__*) ; 
 char* buf_spname (TYPE_1__*) ; 
 int /*<<< orphan*/  build_stl_str_hl (int /*<<< orphan*/ ,char*,int,scalar_t__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int called_emsg ; 
 TYPE_1__* curbuf ; 
 int /*<<< orphan*/  curwin ; 
 char* gettail (int /*<<< orphan*/ *) ; 
 char* gettail_sep (char*) ; 
 int /*<<< orphan*/  gui_macvim_update_modified_flag () ; 
 scalar_t__ has_mbyte ; 
 int /*<<< orphan*/  home_replace (TYPE_1__*,int /*<<< orphan*/ *,char*,int,void*) ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/ * lasticon ; 
 int /*<<< orphan*/ * lasttitle ; 
 scalar_t__ mb_tail_off (char*,char*) ; 
 void* need_maketitle ; 
 scalar_t__ p_icon ; 
 scalar_t__* p_iconstring ; 
 scalar_t__ p_title ; 
 int p_titlelen ; 
 scalar_t__* p_titlestring ; 
 int /*<<< orphan*/  redrawing () ; 
 int /*<<< orphan*/  resettitle () ; 
 int /*<<< orphan*/ * serverName ; 
 int /*<<< orphan*/  set_string_option_direct (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stl_syntax ; 
 scalar_t__ stub1 (char*,char*) ; 
 int ti_change (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  trans_characters (char*,int) ; 
 char* transstr (char*) ; 
 int /*<<< orphan*/  trunc_string (char*,char*,int,int) ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 int /*<<< orphan*/  vim_strcat (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vim_strncpy (char*,char*,size_t) ; 
 int vim_strsize (char*) ; 
 int was_set_insecurely (char*,int /*<<< orphan*/ ) ; 

void
maketitle()
{
    char_u	*p;
    char_u	*t_str = NULL;
    char_u	*i_name;
    char_u	*i_str = NULL;
    int		maxlen = 0;
    int		len;
    int		mustset;
    char_u	buf[IOSIZE];
    int		off;

    if (!redrawing())
    {
	/* Postpone updating the title when 'lazyredraw' is set. */
	need_maketitle = TRUE;
	return;
    }

#ifdef FEAT_GUI_MACVIM
    gui_macvim_update_modified_flag();
#endif

    need_maketitle = FALSE;
    if (!p_title && !p_icon && lasttitle == NULL && lasticon == NULL)
	return;

    if (p_title)
    {
	if (p_titlelen > 0)
	{
	    maxlen = p_titlelen * Columns / 100;
	    if (maxlen < 10)
		maxlen = 10;
	}

	t_str = buf;
	if (*p_titlestring != NUL)
	{
#ifdef FEAT_STL_OPT
	    if (stl_syntax & STL_IN_TITLE)
	    {
		int	use_sandbox = FALSE;
		int	save_called_emsg = called_emsg;

# ifdef FEAT_EVAL
		use_sandbox = was_set_insecurely((char_u *)"titlestring", 0);
# endif
		called_emsg = FALSE;
		build_stl_str_hl(curwin, t_str, sizeof(buf),
					      p_titlestring, use_sandbox,
					      0, maxlen, NULL, NULL);
		if (called_emsg)
		    set_string_option_direct((char_u *)"titlestring", -1,
					   (char_u *)"", OPT_FREE, SID_ERROR);
		called_emsg |= save_called_emsg;
	    }
	    else
#endif
		t_str = p_titlestring;
	}
	else
	{
	    /* format: "fname + (path) (1 of 2) - VIM" */

#define SPACE_FOR_FNAME (IOSIZE - 100)
#define SPACE_FOR_DIR   (IOSIZE - 20)
#define SPACE_FOR_ARGNR (IOSIZE - 10)  /* at least room for " - VIM" */
	    if (curbuf->b_fname == NULL)
		vim_strncpy(buf, (char_u *)_("[No Name]"), SPACE_FOR_FNAME);
	    else
	    {
		p = transstr(gettail(curbuf->b_fname));
		vim_strncpy(buf, p, SPACE_FOR_FNAME);
		vim_free(p);
	    }

	    switch (bufIsChanged(curbuf)
		    + (curbuf->b_p_ro * 2)
		    + (!curbuf->b_p_ma * 4))
	    {
		case 1: STRCAT(buf, " +"); break;
		case 2: STRCAT(buf, " ="); break;
		case 3: STRCAT(buf, " =+"); break;
		case 4:
		case 6: STRCAT(buf, " -"); break;
		case 5:
		case 7: STRCAT(buf, " -+"); break;
	    }

	    if (curbuf->b_fname != NULL)
	    {
		/* Get path of file, replace home dir with ~ */
		off = (int)STRLEN(buf);
		buf[off++] = ' ';
		buf[off++] = '(';
		home_replace(curbuf, curbuf->b_ffname,
					buf + off, SPACE_FOR_DIR - off, TRUE);
#ifdef BACKSLASH_IN_FILENAME
		/* avoid "c:/name" to be reduced to "c" */
		if (isalpha(buf[off]) && buf[off + 1] == ':')
		    off += 2;
#endif
		/* remove the file name */
		p = gettail_sep(buf + off);
		if (p == buf + off)
		    /* must be a help buffer */
		    vim_strncpy(buf + off, (char_u *)_("help"),
					   (size_t)(SPACE_FOR_DIR - off - 1));
		else
		    *p = NUL;

		/* Translate unprintable chars and concatenate.  Keep some
		 * room for the server name.  When there is no room (very long
		 * file name) use (...). */
		if (off < SPACE_FOR_DIR)
		{
		    p = transstr(buf + off);
		    vim_strncpy(buf + off, p, (size_t)(SPACE_FOR_DIR - off));
		    vim_free(p);
		}
		else
		{
		    vim_strncpy(buf + off, (char_u *)"...",
					     (size_t)(SPACE_FOR_ARGNR - off));
		}
		STRCAT(buf, ")");
	    }

#ifndef FEAT_GUI_MACVIM
	    append_arg_number(curwin, buf, SPACE_FOR_ARGNR, FALSE);
#endif

#if defined(FEAT_CLIENTSERVER)
	    if (serverName != NULL)
	    {
		STRCAT(buf, " - ");
		vim_strcat(buf, serverName, IOSIZE);
	    }
	    else
#endif
		STRCAT(buf, " - VIM");

	    if (maxlen > 0)
	    {
		/* make it shorter by removing a bit in the middle */
		if (vim_strsize(buf) > maxlen)
		    trunc_string(buf, buf, maxlen, IOSIZE);
	    }
	}
    }
    mustset = ti_change(t_str, &lasttitle);

    if (p_icon)
    {
	i_str = buf;
	if (*p_iconstring != NUL)
	{
#ifdef FEAT_STL_OPT
	    if (stl_syntax & STL_IN_ICON)
	    {
		int	use_sandbox = FALSE;
		int	save_called_emsg = called_emsg;

# ifdef FEAT_EVAL
		use_sandbox = was_set_insecurely((char_u *)"iconstring", 0);
# endif
		called_emsg = FALSE;
		build_stl_str_hl(curwin, i_str, sizeof(buf),
						    p_iconstring, use_sandbox,
						    0, 0, NULL, NULL);
		if (called_emsg)
		    set_string_option_direct((char_u *)"iconstring", -1,
					   (char_u *)"", OPT_FREE, SID_ERROR);
		called_emsg |= save_called_emsg;
	    }
	    else
#endif
		i_str = p_iconstring;
	}
	else
	{
	    if (buf_spname(curbuf) != NULL)
		i_name = buf_spname(curbuf);
	    else		    /* use file name only in icon */
		i_name = gettail(curbuf->b_ffname);
	    *i_str = NUL;
	    /* Truncate name at 100 bytes. */
	    len = (int)STRLEN(i_name);
	    if (len > 100)
	    {
		len -= 100;
#ifdef FEAT_MBYTE
		if (has_mbyte)
		    len += (*mb_tail_off)(i_name, i_name + len) + 1;
#endif
		i_name += len;
	    }
	    STRCPY(i_str, i_name);
	    trans_characters(i_str, IOSIZE);
	}
    }

    mustset |= ti_change(i_str, &lasticon);

    if (mustset)
	resettitle();
}