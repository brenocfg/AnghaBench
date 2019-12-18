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
 int LIGHT ; 
 int PD0 ; 
 int PD1 ; 
 int PD6 ; 
 int PORTD ; 
 int QWERTY ; 
 int WIN ; 

uint32_t layer_state_set_kb(uint32_t state) {
  if (state & (1<<QWERTY)){
    PORTD &= ~(1 << PD0);
  } else {
    PORTD |= (1 << PD0);
  }

  if (state & (1<<WIN)){
    PORTD &= ~(1 << PD1);
  }
  else{
    PORTD |= (1 << PD1);
  }

  if (state & (1<<LIGHT)){
    PORTD &= ~(1 << PD6);
  }
  else{
    PORTD |= (1 << PD6);
  }
    return state;
}