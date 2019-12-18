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
 size_t** KEY_TO_LED_MAP ; 
 size_t MATRIX_COLS ; 
 size_t MATRIX_ROWS ; 

__attribute__((used)) static uint8_t map_key_position_to_led_index(uint8_t col, uint8_t row) {
  if (row >= 0 && row < MATRIX_ROWS && col >= 0 && col < MATRIX_COLS) {
    return KEY_TO_LED_MAP[row][col];
  }
  return -1;
}