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
 int DDRF ; 
 int PORTB ; 
 int PORTC ; 
 int PORTF ; 

__attribute__((used)) static void unselect_cols(void) {
  DDRB  |=  0b01100000;
  PORTB &= ~0b01100000;

  DDRC  |=  0b11000000;
  PORTC &= ~0b11000000;

  DDRF  |=  0b00000011;
  PORTF &= ~0b00000011;
}