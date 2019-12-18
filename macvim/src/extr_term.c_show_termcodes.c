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
struct TYPE_2__ {int /*<<< orphan*/  code; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int Columns ; 
 int /*<<< orphan*/  FALSE ; 
 int GAP ; 
 int INC2 ; 
 int INC3 ; 
 int /*<<< orphan*/  MSG_PUTS_TITLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ alloc (unsigned int) ; 
 scalar_t__ got_int ; 
 int msg_col ; 
 int /*<<< orphan*/  msg_putchar (char) ; 
 int /*<<< orphan*/  out_flush () ; 
 int show_one_termcode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tc_len ; 
 TYPE_1__* termcodes ; 
 int /*<<< orphan*/  ui_breakcheck () ; 
 int /*<<< orphan*/  vim_free (int*) ; 

void
show_termcodes()
{
    int		col;
    int		*items;
    int		item_count;
    int		run;
    int		row, rows;
    int		cols;
    int		i;
    int		len;

#define INC3 27	    /* try to make three columns */
#define INC2 40	    /* try to make two columns */
#define GAP 2	    /* spaces between columns */

    if (tc_len == 0)	    /* no terminal codes (must be GUI) */
	return;
    items = (int *)alloc((unsigned)(sizeof(int) * tc_len));
    if (items == NULL)
	return;

    /* Highlight title */
    MSG_PUTS_TITLE(_("\n--- Terminal keys ---"));

    /*
     * do the loop two times:
     * 1. display the short items (non-strings and short strings)
     * 2. display the medium items (medium length strings)
     * 3. display the long items (remaining strings)
     */
    for (run = 1; run <= 3 && !got_int; ++run)
    {
	/*
	 * collect the items in items[]
	 */
	item_count = 0;
	for (i = 0; i < tc_len; i++)
	{
	    len = show_one_termcode(termcodes[i].name,
						    termcodes[i].code, FALSE);
	    if (len <= INC3 - GAP ? run == 1
			: len <= INC2 - GAP ? run == 2
			: run == 3)
		items[item_count++] = i;
	}

	/*
	 * display the items
	 */
	if (run <= 2)
	{
	    cols = (Columns + GAP) / (run == 1 ? INC3 : INC2);
	    if (cols == 0)
		cols = 1;
	    rows = (item_count + cols - 1) / cols;
	}
	else	/* run == 3 */
	    rows = item_count;
	for (row = 0; row < rows && !got_int; ++row)
	{
	    msg_putchar('\n');			/* go to next line */
	    if (got_int)			/* 'q' typed in more */
		break;
	    col = 0;
	    for (i = row; i < item_count; i += rows)
	    {
		msg_col = col;			/* make columns */
		show_one_termcode(termcodes[items[i]].name,
					      termcodes[items[i]].code, TRUE);
		if (run == 2)
		    col += INC2;
		else
		    col += INC3;
	    }
	    out_flush();
	    ui_breakcheck();
	}
    }
    vim_free(items);
}