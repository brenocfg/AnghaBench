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
 scalar_t__ MCUSR ; 
 int OCR1A ; 
 int OCR1B ; 
 int OCR1C ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  wdt_disable () ; 
 int /*<<< orphan*/  wdt_reset () ; 

void reset_keyboard_kb(){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    OCR1A = 0x0000; // B5 - Red
    OCR1B = 0x0FFF; // B6 - Green
    OCR1C = 0x0FFF; // B7 - Blue
    reset_keyboard();
}