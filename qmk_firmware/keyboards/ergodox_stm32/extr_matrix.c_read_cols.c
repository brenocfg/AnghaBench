#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ matrix_row_t ;
struct TYPE_2__ {scalar_t__ IDR; } ;

/* Variables and functions */
 TYPE_1__* GPIOB ; 
 int /*<<< orphan*/  I2C_ADDR ; 
 scalar_t__ I2C_GPIOB ; 
 scalar_t__ MATRIX_ROWS_PER_SIDE ; 
 scalar_t__ i2c_readReg (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int,int) ; 
 scalar_t__ mcp23017_status ; 

__attribute__((used)) static matrix_row_t read_cols(uint8_t row) {
  if (row < MATRIX_ROWS_PER_SIDE) {
    uint8_t data = 0xFF;
    if (!mcp23017_status) {
      uint8_t regAddr = I2C_GPIOB;
      mcp23017_status = i2c_readReg(I2C_ADDR, regAddr, &data, 1, 10);
    }
    if (mcp23017_status) {
      return 0;
    }
    return (~data) & 0x3F;
  } else {
      uint8_t data_p = (GPIOB -> IDR);
      uint8_t data = data_p;
    return ((~data) & 0x3f);
  }
}