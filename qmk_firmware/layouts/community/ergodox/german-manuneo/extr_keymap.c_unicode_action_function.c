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
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_PPLS ; 
 int /*<<< orphan*/  KC_U ; 
#define  UC_MODE_LINUX 130 
#define  UC_MODE_OSX 129 
#define  UC_MODE_WIN 128 
 int /*<<< orphan*/  hextokeycode (int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int unicode_mode ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void unicode_action_function(uint16_t hi, uint16_t lo) {
    switch (unicode_mode) {
    case UC_MODE_WIN:
        register_code(KC_LALT);

        register_code(KC_PPLS);
        unregister_code(KC_PPLS);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LALT);
        break;
    case UC_MODE_LINUX:
        register_code(KC_LCTL);
        register_code(KC_LSFT);

        register_code(KC_U);
        unregister_code(KC_U);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        break;
    case UC_MODE_OSX:
        break;
    }
}