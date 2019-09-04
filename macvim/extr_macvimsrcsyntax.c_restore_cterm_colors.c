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
 scalar_t__ cterm_normal_bg_color ; 
 scalar_t__ cterm_normal_fg_bold ; 
 scalar_t__ cterm_normal_fg_color ; 

void
restore_cterm_colors()
{
#if defined(MSDOS) || (defined(WIN3264) && !defined(FEAT_GUI_W32))
    /* Since t_me has been set, this probably means that the user
     * wants to use this as default colors.  Need to reset default
     * background/foreground colors. */
    mch_set_normal_colors();
#else
    cterm_normal_fg_color = 0;
    cterm_normal_fg_bold = 0;
    cterm_normal_bg_color = 0;
#endif
}