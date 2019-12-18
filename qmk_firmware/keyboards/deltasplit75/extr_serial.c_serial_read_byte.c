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
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  serial_delay () ; 
 int /*<<< orphan*/  serial_input () ; 
 int serial_read_pin () ; 

__attribute__((used)) static
uint8_t serial_read_byte(void) {
  uint8_t byte = 0;
  serial_input();
  for ( uint8_t i = 0; i < 8; ++i) {
    byte = (byte << 1) | serial_read_pin();
    serial_delay();
    _delay_us(1);
  }

  return byte;
}