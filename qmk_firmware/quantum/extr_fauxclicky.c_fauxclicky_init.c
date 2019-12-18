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
 int COM3A0 ; 
 int COM3A1 ; 
 int CS30 ; 
 int CS31 ; 
 int CS32 ; 
 int /*<<< orphan*/  DDRC ; 
 int /*<<< orphan*/  PORTC6 ; 
 int TCCR3A ; 
 int TCCR3B ; 
 int WGM30 ; 
 int WGM31 ; 
 int WGM32 ; 
 int WGM33 ; 
 int /*<<< orphan*/  _BV (int /*<<< orphan*/ ) ; 

void fauxclicky_init() {
    // Set port PC6 (OC3A and /OC4A) as output
    DDRC |= _BV(PORTC6);

    // TCCR3A / TCCR3B: Timer/Counter #3 Control Registers
    TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (0 << CS32) | (1 << CS31) | (0 << CS30);
}