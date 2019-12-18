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
 int /*<<< orphan*/  TRUE ; 
 int mouse_active ; 
 int /*<<< orphan*/  mouse_hidden ; 

void
mch_setmouse(int on)
{
    mouse_active = on;
    mouse_hidden = TRUE;	/* don't show it until moved */
}