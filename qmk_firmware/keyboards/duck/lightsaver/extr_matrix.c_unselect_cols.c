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
 int DDRF ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTF ; 

__attribute__((used)) static void unselect_cols(void) {
  DDRB  |=  0b01110000;
  PORTB &= ~0b01110000;

  DDRC |= (1<<6) | (1<<7);
  PORTC &= ~((1<<6) | (1<<7));

  DDRF |= (1<<0) | (1<<1);
  PORTF &= ~((1<<0) | (1<<1));

  DDRD |= (1<<7);
  PORTD &= ~(1<<7);
}