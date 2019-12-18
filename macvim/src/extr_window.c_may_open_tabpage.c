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
struct TYPE_2__ {int tab; } ;

/* Variables and functions */
 int FAIL ; 
 TYPE_1__ cmdmod ; 
 int postponed_split_tab ; 
 int win_new_tabpage (int) ; 

int
may_open_tabpage()
{
    int		n = (cmdmod.tab == 0) ? postponed_split_tab : cmdmod.tab;

    if (n != 0)
    {
	cmdmod.tab = 0;	    /* reset it to avoid doing it twice */
	postponed_split_tab = 0;
	return win_new_tabpage(n);
    }
    return FAIL;
}