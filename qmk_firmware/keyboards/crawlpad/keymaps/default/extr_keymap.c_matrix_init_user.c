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
 int PORTB ; 

void matrix_init_user(void) {
  /* set LED row pins to output and low */
  DDRB |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
  PORTB &= ~(1 << 4) & ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
}