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
#define  BCM2835_I2S_CS_A_REG 131 
#define  BCM2835_I2S_FIFO_A_REG 130 
#define  BCM2835_I2S_GRAY_REG 129 
#define  BCM2835_I2S_INTSTC_A_REG 128 

__attribute__((used)) static bool bcm2835_i2s_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case BCM2835_I2S_CS_A_REG:
	case BCM2835_I2S_FIFO_A_REG:
	case BCM2835_I2S_INTSTC_A_REG:
	case BCM2835_I2S_GRAY_REG:
		return true;
	default:
		return false;
	};
}