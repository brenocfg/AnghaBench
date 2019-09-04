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
#define  I2S_CKR 135 
#define  I2S_CLR 134 
#define  I2S_DMACR 133 
#define  I2S_INTCR 132 
#define  I2S_RXCR 131 
#define  I2S_TXCR 130 
#define  I2S_TXDR 129 
#define  I2S_XFER 128 

__attribute__((used)) static bool rockchip_i2s_wr_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case I2S_TXCR:
	case I2S_RXCR:
	case I2S_CKR:
	case I2S_DMACR:
	case I2S_INTCR:
	case I2S_XFER:
	case I2S_CLR:
	case I2S_TXDR:
		return true;
	default:
		return false;
	}
}