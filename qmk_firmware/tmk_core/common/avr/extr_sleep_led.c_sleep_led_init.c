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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS10 ; 
 int OCR1AH ; 
 int OCR1AL ; 
 int SLEEP_LED_TIMER_TOP ; 
 int /*<<< orphan*/  SREG ; 
 int /*<<< orphan*/  TCCR1B ; 
 int /*<<< orphan*/  WGM12 ; 
 int /*<<< orphan*/  _BV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cli () ; 

void sleep_led_init(void) {
    /* Timer1 setup */
    /* CTC mode */
    TCCR1B |= _BV(WGM12);
    /* Clock selelct: clk/1 */
    TCCR1B |= _BV(CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR1AH = (SLEEP_LED_TIMER_TOP >> 8) & 0xff;
    OCR1AL = SLEEP_LED_TIMER_TOP & 0xff;
    SREG   = sreg;
}