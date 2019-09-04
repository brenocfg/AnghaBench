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
typedef  int int_u ;
typedef  int EventModifiers ;

/* Variables and functions */
 int MOUSE_ALT ; 
 int MOUSE_CTRL ; 
 int MOUSE_SHIFT ; 
 int controlKey ; 
 int optionKey ; 
 int rightControlKey ; 
 int rightOptionKey ; 
 int rightShiftKey ; 
 int shiftKey ; 

int_u
EventModifiers2VimMouseModifiers(EventModifiers macModifiers)
{
    int_u vimModifiers = 0x00;

    if (macModifiers & (shiftKey | rightShiftKey))
	vimModifiers |= MOUSE_SHIFT;
    if (macModifiers & (controlKey | rightControlKey))
	vimModifiers |= MOUSE_CTRL;
    if (macModifiers & (optionKey | rightOptionKey))
	vimModifiers |= MOUSE_ALT;
#if 0
    /* Not yet supported */
    if (macModifiers & (cmdKey)) /* There's no rightCmdKey */
	vimModifiers |= MOUSE_CMD;
#endif
    return (vimModifiers);
}