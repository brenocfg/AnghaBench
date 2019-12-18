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
#define  CS35L34_INT_STATUS_1 131 
#define  CS35L34_INT_STATUS_2 130 
#define  CS35L34_INT_STATUS_3 129 
#define  CS35L34_INT_STATUS_4 128 

__attribute__((used)) static bool cs35l34_precious_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS35L34_INT_STATUS_1:
	case CS35L34_INT_STATUS_2:
	case CS35L34_INT_STATUS_3:
	case CS35L34_INT_STATUS_4:
		return true;
	default:
		return false;
	}
}