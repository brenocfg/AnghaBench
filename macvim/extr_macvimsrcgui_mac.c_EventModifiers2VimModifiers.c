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
 int MOD_MASK_ALT ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_SHIFT ; 
 int controlKey ; 
 int optionKey ; 
 int rightControlKey ; 
 int rightOptionKey ; 
 int rightShiftKey ; 
 int shiftKey ; 

__attribute__((used)) static int_u
EventModifiers2VimModifiers(EventModifiers macModifiers)
{
    int_u vimModifiers = 0x00;

    if (macModifiers & (shiftKey | rightShiftKey))
	vimModifiers |= MOD_MASK_SHIFT;
    if (macModifiers & (controlKey | rightControlKey))
	vimModifiers |= MOD_MASK_CTRL;
    if (macModifiers & (optionKey | rightOptionKey))
	vimModifiers |= MOD_MASK_ALT;
#ifdef USE_CMD_KEY
    if (macModifiers & (cmdKey)) /* There's no rightCmdKey */
	vimModifiers |= MOD_MASK_CMD;
#endif
    return (vimModifiers);
}