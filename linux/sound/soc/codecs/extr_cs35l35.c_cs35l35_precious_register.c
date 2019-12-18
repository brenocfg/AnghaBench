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
#define  CS35L35_INT_STATUS_1 133 
#define  CS35L35_INT_STATUS_2 132 
#define  CS35L35_INT_STATUS_3 131 
#define  CS35L35_INT_STATUS_4 130 
#define  CS35L35_OTP_TRIM_STATUS 129 
#define  CS35L35_PLL_STATUS 128 

__attribute__((used)) static bool cs35l35_precious_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS35L35_INT_STATUS_1:
	case CS35L35_INT_STATUS_2:
	case CS35L35_INT_STATUS_3:
	case CS35L35_INT_STATUS_4:
	case CS35L35_PLL_STATUS:
	case CS35L35_OTP_TRIM_STATUS:
		return true;
	default:
		return false;
	}
}