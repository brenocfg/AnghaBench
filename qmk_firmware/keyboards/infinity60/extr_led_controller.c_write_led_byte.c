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
 int /*<<< orphan*/  is31_write_data (int,int*,int) ; 

void write_led_byte (uint8_t page, uint8_t row, uint8_t led_byte) {
  uint8_t led_control_word[2] = {0};//register address and on/off byte

  led_control_word[0] = (row - 1 ) * 0x02;// A-matrix is every other byte
  led_control_word[1] = led_byte;
  is31_write_data(page, led_control_word, 0x02);
}