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
struct TYPE_2__ {int /*<<< orphan*/  cmdlen; int /*<<< orphan*/ * cmdbuff; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 TYPE_1__ ccline ; 
 scalar_t__ cmd_silent ; 
 int /*<<< orphan*/  cmdline_row ; 
 int /*<<< orphan*/  draw_cmdline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_clr_eos () ; 
 void* msg_no_more ; 
 void* msg_scroll ; 
 int /*<<< orphan*/  msg_start () ; 
 int /*<<< orphan*/  redrawcmdprompt () ; 
 int /*<<< orphan*/  set_cmdspos_cursor () ; 
 void* skip_redraw ; 
 int /*<<< orphan*/  windgoto (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
redrawcmd()
{
    if (cmd_silent)
	return;

    /* when 'incsearch' is set there may be no command line while redrawing */
    if (ccline.cmdbuff == NULL)
    {
	windgoto(cmdline_row, 0);
	msg_clr_eos();
	return;
    }

    msg_start();
    redrawcmdprompt();

    /* Don't use more prompt, truncate the cmdline if it doesn't fit. */
    msg_no_more = TRUE;
    draw_cmdline(0, ccline.cmdlen);
    msg_clr_eos();
    msg_no_more = FALSE;

    set_cmdspos_cursor();

    /*
     * An emsg() before may have set msg_scroll. This is used in normal mode,
     * in cmdline mode we can reset them now.
     */
    msg_scroll = FALSE;		/* next message overwrites cmdline */

    /* Typing ':' at the more prompt may set skip_redraw.  We don't want this
     * in cmdline mode */
    skip_redraw = FALSE;
}