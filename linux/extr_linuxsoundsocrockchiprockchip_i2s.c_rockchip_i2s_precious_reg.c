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
#define  I2S_RXDR 128 

__attribute__((used)) static bool rockchip_i2s_precious_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case I2S_RXDR:
		return true;
	default:
		return false;
	}
}