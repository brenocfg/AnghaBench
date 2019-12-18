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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int Columns ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** features ; 
 int /*<<< orphan*/  got_int ; 
 int msg_col ; 
 int /*<<< orphan*/  msg_putchar (char) ; 
 int /*<<< orphan*/  msg_puts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version_msg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
list_features()
{
    int		i;
    int		ncol;
    int		nrow;
    int		nfeat = 0;
    int		width = 0;

    /* Find the length of the longest feature name, use that + 1 as the column
     * width */
    for (i = 0; features[i] != NULL; ++i)
    {
	int l = (int)STRLEN(features[i]);

	if (l > width)
	    width = l;
	++nfeat;
    }
    width += 1;

    if (Columns < width)
    {
	/* Not enough screen columns - show one per line */
	for (i = 0; features[i] != NULL; ++i)
	{
	    version_msg(features[i]);
	    if (msg_col > 0)
		msg_putchar('\n');
	}
	return;
    }

    /* The rightmost column doesn't need a separator.
     * Sacrifice it to fit in one more column if possible. */
    ncol = (int) (Columns + 1) / width;
    nrow = nfeat / ncol + (nfeat % ncol ? 1 : 0);

    /* i counts columns then rows.  idx counts rows then columns. */
    for (i = 0; !got_int && i < nrow * ncol; ++i)
    {
	int idx = (i / ncol) + (i % ncol) * nrow;

	if (idx < nfeat)
	{
	    int last_col = (i + 1) % ncol == 0;

	    msg_puts((char_u *)features[idx]);
	    if (last_col)
	    {
		if (msg_col > 0)
		    msg_putchar('\n');
	    }
	    else
	    {
		while (msg_col % width)
		    msg_putchar(' ');
	    }
	}
	else
	{
	    if (msg_col > 0)
		msg_putchar('\n');
	}
    }
}