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
struct TYPE_2__ {scalar_t__ cmdfirstc; int cmdindent; int /*<<< orphan*/  cmdattr; int /*<<< orphan*/ * cmdprompt; } ;

/* Variables and functions */
 int Columns ; 
 scalar_t__ NUL ; 
 TYPE_1__ ccline ; 
 scalar_t__ cmd_silent ; 
 int cmdline_row ; 
 int msg_col ; 
 int /*<<< orphan*/  msg_putchar (char) ; 
 int /*<<< orphan*/  msg_puts_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int msg_row ; 

__attribute__((used)) static void
redrawcmdprompt()
{
    int		i;

    if (cmd_silent)
	return;
    if (ccline.cmdfirstc != NUL)
	msg_putchar(ccline.cmdfirstc);
    if (ccline.cmdprompt != NULL)
    {
	msg_puts_attr(ccline.cmdprompt, ccline.cmdattr);
	ccline.cmdindent = msg_col + (msg_row - cmdline_row) * Columns;
	/* do the reverse of set_cmdspos() */
	if (ccline.cmdfirstc != NUL)
	    --ccline.cmdindent;
    }
    else
	for (i = ccline.cmdindent; i > 0; --i)
	    msg_putchar(' ');
}