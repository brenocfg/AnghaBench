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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_PPLS ; 
 int /*<<< orphan*/  hextokeycode (int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void send_unicode(uint16_t unicode)
{
    // For more info on how this works per OS, see here: https://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input
    // Implemented for Windows:
    // Pressing ALT followed by + followed by the unicode code point in hex.
    // Requires registry key HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad set to String 1
    register_code(KC_LALT);
    register_code(KC_PPLS);
    unregister_code(KC_PPLS);

    for (int i = 12; i >= 0; i -= 4) {
        register_code(hextokeycode((unicode >> i) & 0xF));
        unregister_code(hextokeycode((unicode >> i) & 0xF));
    }

    unregister_code(KC_LALT);
}