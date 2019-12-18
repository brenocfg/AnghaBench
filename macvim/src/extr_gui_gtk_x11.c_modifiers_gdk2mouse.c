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
typedef  int guint ;

/* Variables and functions */
 int GDK_CONTROL_MASK ; 
 int GDK_MOD1_MASK ; 
 int GDK_SHIFT_MASK ; 
 int MOUSE_ALT ; 
 int MOUSE_CTRL ; 
 int MOUSE_SHIFT ; 

__attribute__((used)) static int
modifiers_gdk2mouse(guint state)
{
    int modifiers = 0;

    if (state & GDK_SHIFT_MASK)
	modifiers |= MOUSE_SHIFT;
    if (state & GDK_CONTROL_MASK)
	modifiers |= MOUSE_CTRL;
    if (state & GDK_MOD1_MASK)
	modifiers |= MOUSE_ALT;

    return modifiers;
}