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
struct TYPE_2__ {int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  p_cot ; 
 int t_colors ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int
pum_wanted()
{
    /* 'completeopt' must contain "menu" or "menuone" */
    if (vim_strchr(p_cot, 'm') == NULL)
	return FALSE;

    /* The display looks bad on a B&W display. */
    if (t_colors < 8
#ifdef FEAT_GUI
	    && !gui.in_use
#endif
	    )
	return FALSE;
    return TRUE;
}