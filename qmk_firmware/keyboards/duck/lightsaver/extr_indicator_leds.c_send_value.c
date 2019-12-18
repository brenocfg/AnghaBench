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
typedef  enum Device { ____Placeholder_Device } Device ;

/* Variables and functions */
 int Device_STATUSLED ; 
 int /*<<< orphan*/  send_bit_d4 (int) ; 

void send_value(uint8_t byte, enum Device device) {
  for(uint8_t b = 0; b < 8; b++) {
    if(device == Device_STATUSLED) {
      send_bit_d4(byte & 0b10000000);
      byte <<= 1;
    }
  }
}