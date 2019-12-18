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
 int DDRC ; 
 int DDRD ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 

__attribute__((used)) static void unselect_rows(void) {
  // no need to unselect on mcp23018, because the select step sets all
  // the other row bits high, and it's not changing to a different
  // direction

  // unselect on teensy
  // Hi-Z(DDR:0, PORT:0) to unselect
  DDRB &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
  PORTB &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
  DDRD &= ~(1 << 2 | 1 << 3);
  PORTD &= ~(1 << 2 | 1 << 3);
  DDRC &= ~(1 << 6);
  PORTC &= ~(1 << 6);
}