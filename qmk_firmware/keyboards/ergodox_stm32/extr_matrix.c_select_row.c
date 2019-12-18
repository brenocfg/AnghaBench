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
typedef  int uint8_t ;
struct TYPE_2__ {int BRR; } ;

/* Variables and functions */
 TYPE_1__* GPIOB ; 
 int /*<<< orphan*/  I2C_ADDR ; 
 int /*<<< orphan*/  I2C_GPIOA ; 
 int MATRIX_ROWS_PER_SIDE ; 
 scalar_t__ i2c_writeReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 scalar_t__ mcp23017_status ; 

__attribute__((used)) static void select_row(uint8_t row) {
  if (row < MATRIX_ROWS_PER_SIDE) {
    if (!mcp23017_status) {
      uint8_t data = (0xFF & ~(1 << row));
      mcp23017_status = i2c_writeReg(I2C_ADDR, I2C_GPIOA, &data, 1, 10);
    }
  } else {
    GPIOB->BRR = 0x1 << (row+1);
  }
}