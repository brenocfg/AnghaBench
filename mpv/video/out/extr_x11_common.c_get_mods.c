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
 unsigned int ControlMask ; 
 int MP_KEY_MODIFIER_ALT ; 
 int MP_KEY_MODIFIER_CTRL ; 
 int MP_KEY_MODIFIER_META ; 
 int MP_KEY_MODIFIER_SHIFT ; 
 unsigned int Mod1Mask ; 
 unsigned int Mod4Mask ; 
 unsigned int ShiftMask ; 

__attribute__((used)) static int get_mods(unsigned int state)
{
    int modifiers = 0;
    if (state & ShiftMask)
        modifiers |= MP_KEY_MODIFIER_SHIFT;
    if (state & ControlMask)
        modifiers |= MP_KEY_MODIFIER_CTRL;
    if (state & Mod1Mask)
        modifiers |= MP_KEY_MODIFIER_ALT;
    if (state & Mod4Mask)
        modifiers |= MP_KEY_MODIFIER_META;
    return modifiers;
}