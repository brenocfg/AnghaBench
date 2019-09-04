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
struct TYPE_2__ {int /*<<< orphan*/ * tp_next; } ;

/* Variables and functions */
 TYPE_1__* first_tabpage ; 
 int p_stal ; 

int
tabline_height()
{
#ifdef FEAT_GUI_TABLINE
    /* When the GUI has the tabline then this always returns zero. */
    if (gui_use_tabline())
	return 0;
#endif
    switch (p_stal)
    {
	case 0: return 0;
	case 1: return (first_tabpage->tp_next == NULL) ? 0 : 1;
    }
    return 1;
}