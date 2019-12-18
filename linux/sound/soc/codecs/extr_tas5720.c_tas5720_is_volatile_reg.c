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
#define  TAS5720_DEVICE_ID_REG 129 
#define  TAS5720_FAULT_REG 128 

__attribute__((used)) static bool tas5720_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TAS5720_DEVICE_ID_REG:
	case TAS5720_FAULT_REG:
		return true;
	default:
		return false;
	}
}