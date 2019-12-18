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
 int /*<<< orphan*/  DDRB ; 
 int /*<<< orphan*/  DDRE ; 
 int PCICR ; 
 int PCIE0 ; 
 int /*<<< orphan*/  PCMSK0 ; 
 int /*<<< orphan*/  PORTB ; 
 int /*<<< orphan*/  PORTE ; 
 int /*<<< orphan*/  TRKBTN ; 
 int /*<<< orphan*/  TRKMASK ; 
 int /*<<< orphan*/  sei () ; 

__attribute__((used)) static void enableInterrupts(void) {
    #ifdef BALLER
      // Set interrupt mask
      // Set port defs
      DDRB &= ~TRKMASK;
      PORTB |= TRKMASK;
      DDRE &= ~TRKBTN;
      PORTE |= TRKBTN;

      // Interrupt shenanigans
      //EIMSK |= (1 << PCIE0);
      PCMSK0 |= TRKMASK;
      PCICR |= (1 << PCIE0);
      sei();
    #endif

    return;
}