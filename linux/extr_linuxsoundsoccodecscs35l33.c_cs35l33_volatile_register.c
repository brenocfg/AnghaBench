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
#define  CS35L33_DEVID_AB 134 
#define  CS35L33_DEVID_CD 133 
#define  CS35L33_DEVID_E 132 
#define  CS35L33_HG_STATUS 131 
#define  CS35L33_INT_STATUS_1 130 
#define  CS35L33_INT_STATUS_2 129 
#define  CS35L33_REV_ID 128 

__attribute__((used)) static bool cs35l33_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS35L33_DEVID_AB:
	case CS35L33_DEVID_CD:
	case CS35L33_DEVID_E:
	case CS35L33_REV_ID:
	case CS35L33_INT_STATUS_1:
	case CS35L33_INT_STATUS_2:
	case CS35L33_HG_STATUS:
		return true;
	default:
		return false;
	}
}