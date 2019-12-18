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
struct TYPE_2__ {scalar_t__ tb_len; } ;

/* Variables and functions */
 int FALSE ; 
 int INSERT ; 
 int NORMAL_BUSY ; 
 int /*<<< orphan*/  Recording ; 
 int TRUE ; 
 int /*<<< orphan*/  did_cursorhold ; 
 int get_real_state () ; 
 scalar_t__ has_cursorhold () ; 
 int /*<<< orphan*/  ins_compl_active () ; 
 TYPE_1__ typebuf ; 

int
trigger_cursorhold()
{
    int		state;

    if (!did_cursorhold
	    && has_cursorhold()
	    && !Recording
	    && typebuf.tb_len == 0
#ifdef FEAT_INS_EXPAND
	    && !ins_compl_active()
#endif
	    )
    {
	state = get_real_state();
	if (state == NORMAL_BUSY || (state & INSERT) != 0)
	    return TRUE;
    }
    return FALSE;
}