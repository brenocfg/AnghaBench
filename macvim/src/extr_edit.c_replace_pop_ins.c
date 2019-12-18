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

/* Variables and functions */
 int NORMAL ; 
 int State ; 
 int /*<<< orphan*/  dec_cursor () ; 
 int /*<<< orphan*/  ins_char (int) ; 
 int /*<<< orphan*/  mb_replace_pop_ins (int) ; 
 int replace_pop () ; 

__attribute__((used)) static void
replace_pop_ins()
{
    int	    cc;
    int	    oldState = State;

    State = NORMAL;			/* don't want REPLACE here */
    while ((cc = replace_pop()) > 0)
    {
#ifdef FEAT_MBYTE
	mb_replace_pop_ins(cc);
#else
	ins_char(cc);
#endif
	dec_cursor();
    }
    State = oldState;
}