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
struct TYPE_2__ {int cmdspos; } ;

/* Variables and functions */
 int Columns ; 
 scalar_t__ Rows ; 
 TYPE_1__ ccline ; 
 scalar_t__ cmd_silent ; 
 scalar_t__ cmdline_row ; 
 scalar_t__ cmdmsg_rl ; 
 int /*<<< orphan*/  mch_update_cursor () ; 
 int msg_col ; 
 scalar_t__ msg_row ; 
 int /*<<< orphan*/  redrawcmd_preedit () ; 
 int /*<<< orphan*/  windgoto (scalar_t__,int) ; 

__attribute__((used)) static void
cursorcmd()
{
    if (cmd_silent)
	return;

#ifdef FEAT_RIGHTLEFT
    if (cmdmsg_rl)
    {
	msg_row = cmdline_row  + (ccline.cmdspos / (int)(Columns - 1));
	msg_col = (int)Columns - (ccline.cmdspos % (int)(Columns - 1)) - 1;
	if (msg_row <= 0)
	    msg_row = Rows - 1;
    }
    else
#endif
    {
	msg_row = cmdline_row + (ccline.cmdspos / (int)Columns);
	msg_col = ccline.cmdspos % (int)Columns;
	if (msg_row >= Rows)
	    msg_row = Rows - 1;
    }

    windgoto(msg_row, msg_col);
#if defined(FEAT_XIM) && (defined(FEAT_GUI_GTK) || defined(FEAT_GUI_MACVIM))
    redrawcmd_preedit();
#endif
#ifdef MCH_CURSOR_SHAPE
    mch_update_cursor();
#endif
}