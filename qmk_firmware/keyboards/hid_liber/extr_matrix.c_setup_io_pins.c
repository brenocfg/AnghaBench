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
typedef  size_t uint8_t ;

/* Variables and functions */
 int DDRB ; 
 size_t MATRIX_ROWS ; 
 int PORTB ; 
 int /*<<< orphan*/ * row_bit ; 
 int /*<<< orphan*/ ** row_ddr ; 
 int /*<<< orphan*/ ** row_port ; 

__attribute__((used)) static
void setup_io_pins(void) {
  uint8_t row;
  DDRB  |=  0x0E;
  PORTB &= ~0x0E;
  for(row = 0; row < MATRIX_ROWS; row++) {
    *row_ddr[row]  &= ~row_bit[row];
    *row_port[row] &= ~row_bit[row];
  }
}