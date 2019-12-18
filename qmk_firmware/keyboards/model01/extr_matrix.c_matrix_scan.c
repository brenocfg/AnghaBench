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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  LEFT ; 
 int /*<<< orphan*/  RIGHT ; 
 int /*<<< orphan*/  i2c_read_hand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 

uint8_t matrix_scan(void) {
  uint8_t ret = 0;
  ret |= i2c_read_hand(LEFT);
  ret |= i2c_read_hand(RIGHT);
  matrix_scan_quantum();
  return ret;
}