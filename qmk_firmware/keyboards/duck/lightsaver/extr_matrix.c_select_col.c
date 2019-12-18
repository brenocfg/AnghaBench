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
 int PORTC ; 
 int PORTD ; 
 int PORTF ; 

__attribute__((used)) static void select_col(uint8_t col) {
  switch (col) {
    case 0:
      PORTC |= (1<<6);
      break;
    case 1:
      PORTC |= (1<<6);
      PORTF |= (1<<0);
      break;
    case 2:
      PORTC |= (1<<6);
      PORTF |= (1<<1);
      break;
    case 3:
      PORTC |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      break;
    case 4:
      PORTC |= (1<<6);
      PORTC |= (1<<7);
      break;
    case 5:
      PORTC |= (1<<6);
      PORTF |= (1<<0);
      PORTC |= (1<<7);
      break;
    case 6:
      PORTC |= (1<<6);
      PORTF |= (1<<1);
      PORTC |= (1<<7);
      break;
    case 7:
      PORTC |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      PORTC |= (1<<7);
      break;
    case 8:
      PORTB |= (1<<6);
      break;
    case 9:
      PORTB |= (1<<6);
      PORTF |= (1<<0);
      break;
    case 10:
      PORTB |= (1<<6);
      PORTF |= (1<<1);
      break;
    case 11:
      PORTB |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      break;
    case 12:
      PORTB |= (1<<6);
      PORTC |= (1<<7);
      break;
    case 13:
      PORTB |= (1<<6);
      PORTF |= (1<<0);
      PORTC |= (1<<7);
      break;
    case 14:
      PORTB |= (1<<6);
      PORTF |= (1<<1);
      PORTC |= (1<<7);
      break;
    case 15:
      PORTB |= (1<<6);
      PORTF |= (1<<0) | (1<<1);
      PORTC |= (1<<7);
      break;
    case 16:
      PORTB |= (1<<5);
      break;
    case 17:
      PORTB |= (1<<4);
      break;
    case 18:
      PORTD |= (1<<7);
      break;
  }
}