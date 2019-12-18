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
 scalar_t__ i2c_readReg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

uint8_t readDataFromTS(uint8_t reg) {
  uint8_t rx[1] = { 0 };
  if (i2c_readReg(0x1C << 1, reg, rx, 1, 100) == 0) {
    return rx[0];
  }
  return 0;
}