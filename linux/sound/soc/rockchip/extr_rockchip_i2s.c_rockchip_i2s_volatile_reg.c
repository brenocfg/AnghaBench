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
#define  I2S_CLR 132 
#define  I2S_FIFOLR 131 
#define  I2S_INTSR 130 
#define  I2S_RXDR 129 
#define  I2S_TXDR 128 

__attribute__((used)) static bool rockchip_i2s_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case I2S_INTSR:
	case I2S_CLR:
	case I2S_FIFOLR:
	case I2S_TXDR:
	case I2S_RXDR:
		return true;
	default:
		return false;
	}
}