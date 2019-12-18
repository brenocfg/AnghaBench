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
 int MP_KEY_BASE ; 
 int MP_KEY_MODIFIER_MASK ; 
 int MP_KEY_MODIFIER_SHIFT ; 

int mp_normalize_keycode(int keycode)
{
    if (keycode <= 0)
        return keycode;
    int code = keycode & ~MP_KEY_MODIFIER_MASK;
    int mod = keycode & MP_KEY_MODIFIER_MASK;
    /* On normal keyboards shift changes the character code of non-special
     * keys, so don't count the modifier separately for those. In other words
     * we want to have "a" and "A" instead of "a" and "Shift+A"; but a separate
     * shift modifier is still kept for special keys like arrow keys. */
    if (code >= 32 && code < MP_KEY_BASE) {
        /* Still try to support ASCII case-modifications properly. For example,
         * we want to change "Shift+a" to "A", not "a". Doing this for unicode
         * in general would require huge lookup tables, or a libc with proper
         * unicode support, so we don't do that. */
        if (code >= 'a' && code <= 'z' && (mod & MP_KEY_MODIFIER_SHIFT))
            code &= 0x5F;
        mod &= ~MP_KEY_MODIFIER_SHIFT;
    }
    return code | mod;
}