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
#define  TAS5713_DEVICE_ID 129 
#define  TAS5713_ERROR_STATUS 128 

__attribute__((used)) static bool tas5713_reg_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
		case TAS5713_DEVICE_ID:
		case TAS5713_ERROR_STATUS:
			return true;
	default:
			return false;
	}
}