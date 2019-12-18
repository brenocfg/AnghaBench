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
 int /*<<< orphan*/  IS_BREAK (int) ; 
 int KEY (int) ; 
#define  M0110_ARROW_DOWN 133 
#define  M0110_ARROW_LEFT 132 
#define  M0110_ARROW_RIGHT 131 
#define  M0110_ARROW_UP 130 
 int M0110_CALC_OFFSET ; 
#define  M0110_KEYPAD 129 
 int M0110_KEYPAD_OFFSET ; 
#define  M0110_SHIFT 128 
 int instant () ; 
 int /*<<< orphan*/  print (char*) ; 
 int raw2scan (int) ; 

uint8_t m0110_recv_key(void) {
    static uint8_t keybuf  = 0x00;
    static uint8_t keybuf2 = 0x00;
    static uint8_t rawbuf  = 0x00;
    uint8_t        raw, raw2, raw3;

    if (keybuf) {
        raw    = keybuf;
        keybuf = 0x00;
        return raw;
    }
    if (keybuf2) {
        raw     = keybuf2;
        keybuf2 = 0x00;
        return raw;
    }

    if (rawbuf) {
        raw    = rawbuf;
        rawbuf = 0x00;
    } else {
        raw = instant();  // Use INSTANT for better response. Should be INQUIRY ?
    }
    switch (KEY(raw)) {
        case M0110_KEYPAD:
            raw2 = instant();
            switch (KEY(raw2)) {
                case M0110_ARROW_UP:
                case M0110_ARROW_DOWN:
                case M0110_ARROW_LEFT:
                case M0110_ARROW_RIGHT:
                    if (IS_BREAK(raw2)) {
                        // Case B,F,N:
                        keybuf = (raw2scan(raw2) | M0110_CALC_OFFSET);  // Calc(u)
                        return (raw2scan(raw2) | M0110_KEYPAD_OFFSET);  // Arrow(u)
                    }
                    break;
            }
            // Keypad or Arrow
            return (raw2scan(raw2) | M0110_KEYPAD_OFFSET);
            break;
        case M0110_SHIFT:
            raw2 = instant();
            switch (KEY(raw2)) {
                case M0110_SHIFT:
                    // Case: 5-8,C,G,H
                    rawbuf = raw2;
                    return raw2scan(raw);  // Shift(d/u)
                    break;
                case M0110_KEYPAD:
                    // Shift + Arrow, Calc, or etc.
                    raw3 = instant();
                    switch (KEY(raw3)) {
                        case M0110_ARROW_UP:
                        case M0110_ARROW_DOWN:
                        case M0110_ARROW_LEFT:
                        case M0110_ARROW_RIGHT:
                            if (IS_BREAK(raw)) {
                                if (IS_BREAK(raw3)) {
                                    // Case 4:
                                    print("(4)\n");
                                    keybuf2 = raw2scan(raw);                         // Shift(u)
                                    keybuf  = (raw2scan(raw3) | M0110_CALC_OFFSET);  // Calc(u)
                                    return (raw2scan(raw3) | M0110_KEYPAD_OFFSET);   // Arrow(u)
                                } else {
                                    // Case 3:
                                    print("(3)\n");
                                    return (raw2scan(raw));  // Shift(u)
                                }
                            } else {
                                if (IS_BREAK(raw3)) {
                                    // Case 2:
                                    print("(2)\n");
                                    keybuf = (raw2scan(raw3) | M0110_CALC_OFFSET);  // Calc(u)
                                    return (raw2scan(raw3) | M0110_KEYPAD_OFFSET);  // Arrow(u)
                                } else {
                                    // Case 1:
                                    print("(1)\n");
                                    return (raw2scan(raw3) | M0110_CALC_OFFSET);  // Calc(d)
                                }
                            }
                            break;
                        default:
                            // Shift + Keypad
                            keybuf = (raw2scan(raw3) | M0110_KEYPAD_OFFSET);
                            return raw2scan(raw);  // Shift(d/u)
                            break;
                    }
                    break;
                default:
                    // Shift + Normal keys
                    keybuf = raw2scan(raw2);
                    return raw2scan(raw);  // Shift(d/u)
                    break;
            }
            break;
        default:
            // Normal keys
            return raw2scan(raw);
            break;
    }
}