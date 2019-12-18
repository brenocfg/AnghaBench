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
 int /*<<< orphan*/  B1 ; 
 int /*<<< orphan*/  B2 ; 
 int /*<<< orphan*/  B3 ; 
 int /*<<< orphan*/  B4 ; 
 int /*<<< orphan*/  D7 ; 
 int F_ROW_MASK ; 
 int WASD_MASK ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void backlight_set(uint8_t level) {
    // F-row
    if (level & F_ROW_MASK) {
        writePinHigh(B1);
    } else {
        writePinLow(B1);
    }

    // WASD
    if (level & WASD_MASK) {
        writePinLow(B2);
        writePinLow(B3);
        writePinLow(B4);
        writePinLow(D7);
    } else {
        writePinHigh(B2);
        writePinHigh(B3);
        writePinHigh(B4);
        writePinHigh(D7);
    }
}