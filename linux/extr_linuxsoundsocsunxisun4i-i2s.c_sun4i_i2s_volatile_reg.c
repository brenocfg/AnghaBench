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
struct device {int dummy; } ;

/* Variables and functions */
#define  SUN4I_I2S_FIFO_RX_REG 131 
#define  SUN4I_I2S_INT_STA_REG 130 
#define  SUN4I_I2S_RX_CNT_REG 129 
#define  SUN4I_I2S_TX_CNT_REG 128 

__attribute__((used)) static bool sun4i_i2s_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SUN4I_I2S_FIFO_RX_REG:
	case SUN4I_I2S_INT_STA_REG:
	case SUN4I_I2S_RX_CNT_REG:
	case SUN4I_I2S_TX_CNT_REG:
		return true;

	default:
		return false;
	}
}