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
 int DDRB ; 
 int /*<<< orphan*/  DDRC ; 
 int ICR1 ; 
 int OCR1A ; 
 int OCR1B ; 
 int OCR1C ; 
 int /*<<< orphan*/  PORTC ; 
 int TCCR1A ; 
 int TCCR1B ; 
 int /*<<< orphan*/  WDTO_500MS ; 
 int /*<<< orphan*/  cbi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  issi_init () ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  sbi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wdt_enable (int /*<<< orphan*/ ) ; 

void matrix_init_kb(void)
{
    matrix_init_user();

    // Configure the Layer LED
    // Set up 16 bit PWM: Fast PWM, mode 15, inverted
    TCCR1A = 0b11111110;
    TCCR1B = 0b00011001;
    ICR1 = 0xFFFF;
    // PWM values - 0xFFFF = off, 0x0000 = max
    OCR1C = 0x0000; // B7 - Blue
    OCR1B = 0x0000; // B6 - Green
    OCR1A = 0x0FFF; // B5 - Red
    // Set as output
    DDRB |= 0b11100000;

#ifndef AUDIO_ENABLE
    // If we're not using the audio pin, drive it low
    sbi(DDRC, 6);
    cbi(PORTC, 6);
#endif

#ifdef ISSI_ENABLE
    issi_init();
#endif
#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif

}