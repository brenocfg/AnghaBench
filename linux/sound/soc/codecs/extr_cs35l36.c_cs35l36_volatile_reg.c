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
#define  CS35L36_DEVICE_ID 152 
#define  CS35L36_FAB_ID 151 
#define  CS35L36_HW_REV 150 
#define  CS35L36_INT1_EDGE_LVL_CTRL 149 
#define  CS35L36_INT1_MASK 148 
#define  CS35L36_INT1_RAW_STATUS 147 
#define  CS35L36_INT1_STATUS 146 
#define  CS35L36_INT2_MASK 145 
#define  CS35L36_INT2_RAW_STATUS 144 
#define  CS35L36_INT2_STATUS 143 
#define  CS35L36_INT3_EDGE_LVL_CTRL 142 
#define  CS35L36_INT3_MASK 141 
#define  CS35L36_INT3_RAW_STATUS 140 
#define  CS35L36_INT3_STATUS 139 
#define  CS35L36_INT4_MASK 138 
#define  CS35L36_INT4_RAW_STATUS 137 
#define  CS35L36_INT4_STATUS 136 
#define  CS35L36_PAC_INT_FLUSH_CTRL 135 
#define  CS35L36_PAC_INT_RAW_STATUS 134 
#define  CS35L36_PAC_INT_STATUS 133 
 unsigned int CS35L36_PAC_PMEM_WORD0 ; 
 unsigned int CS35L36_PAC_PMEM_WORD1023 ; 
#define  CS35L36_REV_ID 132 
#define  CS35L36_SW_RESET 131 
#define  CS35L36_SW_REV 130 
#define  CS35L36_TESTKEY_CTRL 129 
#define  CS35L36_USERKEY_CTL 128 

__attribute__((used)) static bool cs35l36_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS35L36_SW_RESET:
	case CS35L36_SW_REV:
	case CS35L36_HW_REV:
	case CS35L36_TESTKEY_CTRL:
	case CS35L36_USERKEY_CTL:
	case CS35L36_DEVICE_ID:
	case CS35L36_FAB_ID:
	case CS35L36_REV_ID:
	case CS35L36_INT1_STATUS:
	case CS35L36_INT2_STATUS:
	case CS35L36_INT3_STATUS:
	case CS35L36_INT4_STATUS:
	case CS35L36_INT1_RAW_STATUS:
	case CS35L36_INT2_RAW_STATUS:
	case CS35L36_INT3_RAW_STATUS:
	case CS35L36_INT4_RAW_STATUS:
	case CS35L36_INT1_MASK:
	case CS35L36_INT2_MASK:
	case CS35L36_INT3_MASK:
	case CS35L36_INT4_MASK:
	case CS35L36_INT1_EDGE_LVL_CTRL:
	case CS35L36_INT3_EDGE_LVL_CTRL:
	case CS35L36_PAC_INT_STATUS:
	case CS35L36_PAC_INT_RAW_STATUS:
	case CS35L36_PAC_INT_FLUSH_CTRL:
		return true;
	default:
		if (reg >= CS35L36_PAC_PMEM_WORD0 &&
			reg <= CS35L36_PAC_PMEM_WORD1023)
			return true;
		else
			return false;
	}
}