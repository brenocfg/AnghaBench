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
#define  CS35L36_TESTKEY_CTRL 130 
#define  CS35L36_TST_FS_MON0 129 
#define  CS35L36_USERKEY_CTL 128 

__attribute__((used)) static bool cs35l36_precious_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS35L36_TESTKEY_CTRL:
	case CS35L36_USERKEY_CTL:
	case CS35L36_TST_FS_MON0:
		return true;
	default:
		return false;
	}
}