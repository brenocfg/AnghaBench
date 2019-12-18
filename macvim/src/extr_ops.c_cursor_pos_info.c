#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct block_def {scalar_t__ textlen; int /*<<< orphan*/ * textstart; } ;
struct TYPE_15__ {scalar_t__ col; int lnum; } ;
typedef  TYPE_2__ pos_T ;
struct TYPE_16__ {int is_VIsual; scalar_t__ start_vcol; scalar_t__ end_vcol; int /*<<< orphan*/  op_type; int /*<<< orphan*/  block_mode; } ;
typedef  TYPE_3__ oparg_T ;
typedef  int linenr_T ;
typedef  long colnr_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_14__ {int ml_flags; int ml_line_count; } ;
struct TYPE_18__ {TYPE_1__ b_ml; scalar_t__ b_p_bin; int /*<<< orphan*/  b_p_eol; } ;
struct TYPE_17__ {scalar_t__ w_curswant; TYPE_2__ w_cursor; scalar_t__ w_virtcol; } ;

/* Variables and functions */
#define  Ctrl_V 128 
 scalar_t__ EOL_DOS ; 
 int /*<<< orphan*/  IOSIZE ; 
 int /*<<< orphan*/ * IObuff ; 
 scalar_t__ MAXCOL ; 
 int /*<<< orphan*/  MAYBE ; 
 int ML_EMPTY ; 
 int /*<<< orphan*/  MSG (char*) ; 
 int /*<<< orphan*/  NUL ; 
 int /*<<< orphan*/  OP_NOP ; 
 int STRLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ VIsual ; 
 scalar_t__ VIsual_active ; 
 int VIsual_mode ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  block_prep (TYPE_3__*,struct block_def*,int,int /*<<< orphan*/ ) ; 
 long bomb_size () ; 
 int /*<<< orphan*/  col_print (int /*<<< orphan*/ *,int,int,int) ; 
 TYPE_9__* curbuf ; 
 TYPE_6__* curwin ; 
 int /*<<< orphan*/ * empty_option ; 
 scalar_t__ get_fileformat (TYPE_9__*) ; 
 int /*<<< orphan*/  getvcols (TYPE_6__*,TYPE_2__*,TYPE_2__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ got_int ; 
 long line_count_info (int /*<<< orphan*/ *,long*,long*,long,int) ; 
 int linetabsize (int /*<<< orphan*/ *) ; 
 scalar_t__ lt (TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/ * ml_get (int) ; 
 int /*<<< orphan*/ * ml_get_curline () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ *) ; 
 char* no_lines_msg ; 
 int /*<<< orphan*/ * p_sbr ; 
 char* p_sel ; 
 int /*<<< orphan*/ * p_shm ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  ui_breakcheck () ; 
 int /*<<< orphan*/  validate_virtcol () ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  virtual_active () ; 
 int /*<<< orphan*/  virtual_op ; 

void
cursor_pos_info()
{
    char_u	*p;
    char_u	buf1[50];
    char_u	buf2[40];
    linenr_T	lnum;
    long	byte_count = 0;
    long	byte_count_cursor = 0;
    long	char_count = 0;
    long	char_count_cursor = 0;
    long	word_count = 0;
    long	word_count_cursor = 0;
    int		eol_size;
    long	last_check = 100000L;
    long	line_count_selected = 0;
    pos_T	min_pos, max_pos;
    oparg_T	oparg;
    struct block_def	bd;

    /*
     * Compute the length of the file in characters.
     */
    if (curbuf->b_ml.ml_flags & ML_EMPTY)
    {
	MSG(_(no_lines_msg));
    }
    else
    {
	if (get_fileformat(curbuf) == EOL_DOS)
	    eol_size = 2;
	else
	    eol_size = 1;

	if (VIsual_active)
	{
	    if (lt(VIsual, curwin->w_cursor))
	    {
		min_pos = VIsual;
		max_pos = curwin->w_cursor;
	    }
	    else
	    {
		min_pos = curwin->w_cursor;
		max_pos = VIsual;
	    }
	    if (*p_sel == 'e' && max_pos.col > 0)
		--max_pos.col;

	    if (VIsual_mode == Ctrl_V)
	    {
#ifdef FEAT_LINEBREAK
		char_u * saved_sbr = p_sbr;

		/* Make 'sbr' empty for a moment to get the correct size. */
		p_sbr = empty_option;
#endif
		oparg.is_VIsual = 1;
		oparg.block_mode = TRUE;
		oparg.op_type = OP_NOP;
		getvcols(curwin, &min_pos, &max_pos,
					  &oparg.start_vcol, &oparg.end_vcol);
#ifdef FEAT_LINEBREAK
		p_sbr = saved_sbr;
#endif
		if (curwin->w_curswant == MAXCOL)
		    oparg.end_vcol = MAXCOL;
		/* Swap the start, end vcol if needed */
		if (oparg.end_vcol < oparg.start_vcol)
		{
		    oparg.end_vcol += oparg.start_vcol;
		    oparg.start_vcol = oparg.end_vcol - oparg.start_vcol;
		    oparg.end_vcol -= oparg.start_vcol;
		}
	    }
	    line_count_selected = max_pos.lnum - min_pos.lnum + 1;
	}

	for (lnum = 1; lnum <= curbuf->b_ml.ml_line_count; ++lnum)
	{
	    /* Check for a CTRL-C every 100000 characters. */
	    if (byte_count > last_check)
	    {
		ui_breakcheck();
		if (got_int)
		    return;
		last_check = byte_count + 100000L;
	    }

	    /* Do extra processing for VIsual mode. */
	    if (VIsual_active
		    && lnum >= min_pos.lnum && lnum <= max_pos.lnum)
	    {
		char_u	    *s = NULL;
		long	    len = 0L;

		switch (VIsual_mode)
		{
		    case Ctrl_V:
#ifdef FEAT_VIRTUALEDIT
			virtual_op = virtual_active();
#endif
			block_prep(&oparg, &bd, lnum, 0);
#ifdef FEAT_VIRTUALEDIT
			virtual_op = MAYBE;
#endif
			s = bd.textstart;
			len = (long)bd.textlen;
			break;
		    case 'V':
			s = ml_get(lnum);
			len = MAXCOL;
			break;
		    case 'v':
			{
			    colnr_T start_col = (lnum == min_pos.lnum)
							   ? min_pos.col : 0;
			    colnr_T end_col = (lnum == max_pos.lnum)
				      ? max_pos.col - start_col + 1 : MAXCOL;

			    s = ml_get(lnum) + start_col;
			    len = end_col;
			}
			break;
		}
		if (s != NULL)
		{
		    byte_count_cursor += line_count_info(s, &word_count_cursor,
					   &char_count_cursor, len, eol_size);
		    if (lnum == curbuf->b_ml.ml_line_count
			    && !curbuf->b_p_eol
			    && curbuf->b_p_bin
			    && (long)STRLEN(s) < len)
			byte_count_cursor -= eol_size;
		}
	    }
	    else
	    {
		/* In non-visual mode, check for the line the cursor is on */
		if (lnum == curwin->w_cursor.lnum)
		{
		    word_count_cursor += word_count;
		    char_count_cursor += char_count;
		    byte_count_cursor = byte_count +
			line_count_info(ml_get(lnum),
				&word_count_cursor, &char_count_cursor,
				  (long)(curwin->w_cursor.col + 1), eol_size);
		}
	    }
	    /* Add to the running totals */
	    byte_count += line_count_info(ml_get(lnum), &word_count,
					 &char_count, (long)MAXCOL, eol_size);
	}

	/* Correction for when last line doesn't have an EOL. */
	if (!curbuf->b_p_eol && curbuf->b_p_bin)
	    byte_count -= eol_size;

	if (VIsual_active)
	{
	    if (VIsual_mode == Ctrl_V && curwin->w_curswant < MAXCOL)
	    {
		getvcols(curwin, &min_pos, &max_pos, &min_pos.col,
								&max_pos.col);
		vim_snprintf((char *)buf1, sizeof(buf1), _("%ld Cols; "),
			(long)(oparg.end_vcol - oparg.start_vcol + 1));
	    }
	    else
		buf1[0] = NUL;

	    if (char_count_cursor == byte_count_cursor
						  && char_count == byte_count)
		vim_snprintf((char *)IObuff, IOSIZE,
			_("Selected %s%ld of %ld Lines; %ld of %ld Words; %ld of %ld Bytes"),
			buf1, line_count_selected,
			(long)curbuf->b_ml.ml_line_count,
			word_count_cursor, word_count,
			byte_count_cursor, byte_count);
	    else
		vim_snprintf((char *)IObuff, IOSIZE,
			_("Selected %s%ld of %ld Lines; %ld of %ld Words; %ld of %ld Chars; %ld of %ld Bytes"),
			buf1, line_count_selected,
			(long)curbuf->b_ml.ml_line_count,
			word_count_cursor, word_count,
			char_count_cursor, char_count,
			byte_count_cursor, byte_count);
	}
	else
	{
	    p = ml_get_curline();
	    validate_virtcol();
	    col_print(buf1, sizeof(buf1), (int)curwin->w_cursor.col + 1,
		    (int)curwin->w_virtcol + 1);
	    col_print(buf2, sizeof(buf2), (int)STRLEN(p),
				linetabsize(p));

	    if (char_count_cursor == byte_count_cursor
		    && char_count == byte_count)
		vim_snprintf((char *)IObuff, IOSIZE,
		    _("Col %s of %s; Line %ld of %ld; Word %ld of %ld; Byte %ld of %ld"),
		    (char *)buf1, (char *)buf2,
		    (long)curwin->w_cursor.lnum,
		    (long)curbuf->b_ml.ml_line_count,
		    word_count_cursor, word_count,
		    byte_count_cursor, byte_count);
	    else
		vim_snprintf((char *)IObuff, IOSIZE,
		    _("Col %s of %s; Line %ld of %ld; Word %ld of %ld; Char %ld of %ld; Byte %ld of %ld"),
		    (char *)buf1, (char *)buf2,
		    (long)curwin->w_cursor.lnum,
		    (long)curbuf->b_ml.ml_line_count,
		    word_count_cursor, word_count,
		    char_count_cursor, char_count,
		    byte_count_cursor, byte_count);
	}

#ifdef FEAT_MBYTE
	byte_count = bomb_size();
	if (byte_count > 0)
	    sprintf((char *)IObuff + STRLEN(IObuff), _("(+%ld for BOM)"),
								  byte_count);
#endif
	/* Don't shorten this message, the user asked for it. */
	p = p_shm;
	p_shm = (char_u *)"";
	msg(IObuff);
	p_shm = p;
    }
}