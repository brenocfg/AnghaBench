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

__attribute__((used)) static void select_col(uint8_t col) {
  switch (col) {
  case  0: PORTB = (PORTB & ~0b01111111) | 0b01100100; break;
  case  1: PORTB = (PORTB & ~0b01111111) | 0b01101100; break;
  case  2: PORTB = (PORTB & ~0b01111111) | 0b01100010; break;
  case  3: PORTB = (PORTB & ~0b01111111) | 0b01111010; break;
  case  4: PORTB = (PORTB & ~0b01111111) | 0b01100110; break;
  case  5: PORTB = (PORTB & ~0b01111111) | 0b01110110; break;
  case  6: PORTB = (PORTB & ~0b01111111) | 0b01101110; break;
  case  7: PORTB = (PORTB & ~0b01111111) | 0b01111110; break;
  case  8: PORTB = (PORTB & ~0b01111111) | 0b01000001; break;
  case  9: PORTB = (PORTB & ~0b01111111) | 0b00100001; break;
  case 10: PORTB = (PORTB & ~0b01111111) | 0b01101010; break;
  case 11: PORTB = (PORTB & ~0b01111111) | 0b01110010; break;
  case 12: PORTB = (PORTB & ~0b01111111) | 0b01111100; break;
  case 13: PORTB = (PORTB & ~0b01111111) | 0b01110100; break;
  case 14: PORTB = (PORTB & ~0b01111111) | 0b01111000; break;
  case 15: PORTB = (PORTB & ~0b01111111) | 0b01110000; break;
  case 16: PORTB = (PORTB & ~0b01111111) | 0b01100000; break;
  case 17: PORTB = (PORTB & ~0b01111111) | 0b01101000; break;
  }
}