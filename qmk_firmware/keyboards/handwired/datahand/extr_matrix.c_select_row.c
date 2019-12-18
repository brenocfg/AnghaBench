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
 int PORTB ; 
 int PORTD ; 
 int PORTE ; 

__attribute__((used)) static void select_row(uint8_t row) {
  /* Original 8051: P1 bits 0-3 (pins 1-4)
   * Teensy++: PE0, PB7, PD0, PD1
   */

  if (row & (1<<0)) {
    PORTE |= (1<<6);
  } else {
    PORTE &= ~(1<<6);
  }

  if (row & (1<<1)) {
    PORTB |= (1<<7);
  } else {
    PORTB &= ~(1<<7);
  }

  if (row & (1<<2)) {
    PORTD |= (1<<0);
  } else {
    PORTD &= ~(1<<0);
  }

  if (row & (1<<3)) {
    PORTD |= (1<<1);
  } else {
    PORTD &= ~(1<<1);
  }
}