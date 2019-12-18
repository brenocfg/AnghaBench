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
 scalar_t__ i2c_transmit (int,int*,int,int) ; 

uint8_t writeDataToTS(uint8_t reg, uint8_t data) {
  uint8_t tx[2] = { reg, data };
  if (i2c_transmit(0x1C << 1, tx, 2, 100) == 0) {
    return 1;
  } else {
    return 0;
  }
}