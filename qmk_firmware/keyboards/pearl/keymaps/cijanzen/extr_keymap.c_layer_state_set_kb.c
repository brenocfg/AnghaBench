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
typedef  int uint32_t ;

/* Variables and functions */
 int PD0 ; 
 int PD1 ; 
 int PD6 ; 
 int PORTD ; 

uint32_t layer_state_set_kb(uint32_t state)
{
  if (state & (1<<1)) { // if we are on layer 1
    PORTD |= (1 << PD0); // light num lock led
  } else if (state & (1<<2)) { // if we are on layer 2

    if (state & (1<<4)) {
      PORTD |= (1 << PD0); // light all indicator leds
      PORTD |= (1 << PD1);
      PORTD |= (1 << PD6);
    } else {
      PORTD &= ~(1 << PD0);
      PORTD |= (1 << PD1); // light caps lock led
      PORTD &= ~(1 << PD6);
    }
  } else if (state & (1<<3)) { // if we are on layer 3
    PORTD |= (1 << PD6); // light scroll lock led
  } else if (state & (1<<4)) { // if we are stuck on layer 4
    PORTD |= (1 << PD0); // light all indicator leds
    PORTD |= (1 << PD1);
    PORTD |= (1 << PD6);
  } else {
    PORTD &= ~(1 << PD0);
    PORTD &= ~(1 << PD1);
    PORTD &= ~(1 << PD6);
  }

  return state;
}