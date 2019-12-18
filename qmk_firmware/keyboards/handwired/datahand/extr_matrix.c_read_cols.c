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
typedef  int matrix_row_t ;

/* Variables and functions */
 int PIND ; 

__attribute__((used)) static matrix_row_t read_cols(void) {
  /* Original 8051: P1 bits 4-7 (pins 5-8)
   * Teensy++: PD bits 2-5
   */

  return (PIND & 0b00111100) >> 2;
}