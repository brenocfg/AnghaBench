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
 int Columns ; 
 int Rows ; 
 int /*<<< orphan*/  mouse_area () ; 
 int mouse_x_div ; 
 int mouse_y_div ; 
 int /*<<< orphan*/  set_window () ; 

void
mch_new_shellsize()
{
#ifdef FEAT_MOUSE
    /* best guess for mouse coordinate computations */
    if (Columns <= 40)
	mouse_x_div = 16;
    if (Rows == 30)
	mouse_y_div = 16;
#endif
    set_window();
#ifdef FEAT_MOUSE
    mouse_area();	/* set area where mouse can go */
#endif
}