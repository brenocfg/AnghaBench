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
 int /*<<< orphan*/  JTD ; 
 int /*<<< orphan*/  MCUCR ; 
 int /*<<< orphan*/  MCUCSR ; 
 int /*<<< orphan*/  _BV (int /*<<< orphan*/ ) ; 

void disable_jtag(void) {
// To use PF4-7 (PC2-5 on ATmega32A), disable JTAG by writing JTD bit twice within four cycles.
#if (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);
#elif defined(__AVR_ATmega32A__)
    MCUCSR |= _BV(JTD);
    MCUCSR |= _BV(JTD);
#endif
}