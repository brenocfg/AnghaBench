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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t move_e0code(uint8_t code) {
    switch(code) {
        // Original IBM XT keyboard has these keys
        case 0x37: return 0x54; // Print Screen
        case 0x46: return 0x55; // Ctrl + Pause
        case 0x1C: return 0x6F; // Keypad Enter
        case 0x35: return 0x7F; // Keypad /

        // Any XT keyobard with these keys?
        // http://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/translate.pdf
        // https://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/scancode.doc
        case 0x5B: return 0x5A; // Left  GUI
        case 0x5C: return 0x5B; // Right GUI
        case 0x5D: return 0x5C; // Application
        case 0x5E: return 0x5D; // Power(not used)
        case 0x5F: return 0x5E; // Sleep(not used)
        case 0x63: return 0x5F; // Wake (not used)
        case 0x48: return 0x60; // Up
        case 0x4B: return 0x61; // Left
        case 0x50: return 0x62; // Down
        case 0x4D: return 0x63; // Right
        case 0x52: return 0x71; // Insert
        case 0x53: return 0x72; // Delete
        case 0x47: return 0x74; // Home
        case 0x4F: return 0x75; // End
        case 0x49: return 0x77; // Home
        case 0x51: return 0x78; // End
        case 0x1D: return 0x7A; // Right Ctrl
        case 0x38: return 0x7C; // Right Alt
    }
    return 0x00;
}