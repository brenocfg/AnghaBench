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
 int /*<<< orphan*/  serial_delay () ; 
 int /*<<< orphan*/  serial_high () ; 
 int /*<<< orphan*/  serial_low () ; 
 int /*<<< orphan*/  serial_output () ; 

__attribute__((used)) static
void serial_write_byte(uint8_t data) {
  uint8_t b = 8;
  serial_output();
  while( b-- ) {
    if(data & (1 << b)) {
      serial_high();
    } else {
      serial_low();
    }
    serial_delay();
  }
}