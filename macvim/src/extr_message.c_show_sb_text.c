#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * sb_prev; } ;
typedef  TYPE_1__ msgchunk_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  do_more_prompt (char) ; 
 int /*<<< orphan*/  last_msgchunk ; 
 TYPE_1__* msg_sb_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_beep () ; 
 int /*<<< orphan*/  wait_return (int /*<<< orphan*/ ) ; 

void
show_sb_text()
{
    msgchunk_T	*mp;

    /* Only show something if there is more than one line, otherwise it looks
     * weird, typing a command without output results in one line. */
    mp = msg_sb_start(last_msgchunk);
    if (mp == NULL || mp->sb_prev == NULL)
	vim_beep();
    else
    {
	do_more_prompt('G');
	wait_return(FALSE);
    }
}