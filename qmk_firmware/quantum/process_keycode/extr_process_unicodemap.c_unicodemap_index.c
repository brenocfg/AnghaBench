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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int IS_HOST_LED_ON (int /*<<< orphan*/ ) ; 
 int MOD_MASK_SHIFT ; 
 scalar_t__ QK_UNICODEMAP ; 
 scalar_t__ QK_UNICODEMAP_PAIR ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int unicode_saved_mods ; 

__attribute__((weak)) uint16_t unicodemap_index(uint16_t keycode) {
    if (keycode >= QK_UNICODEMAP_PAIR) {
        // Keycode is a pair: extract index based on Shift / Caps Lock state
        uint16_t index = keycode - QK_UNICODEMAP_PAIR;

        bool shift = unicode_saved_mods & MOD_MASK_SHIFT, caps = IS_HOST_LED_ON(USB_LED_CAPS_LOCK);
        if (shift ^ caps) {
            index >>= 7;
        }

        return index & 0x7F;
    } else {
        // Keycode is a regular index
        return keycode - QK_UNICODEMAP;
    }
}