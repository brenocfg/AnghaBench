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
#define  MAX98925_FLAG0 139 
#define  MAX98925_FLAG1 138 
#define  MAX98925_FLAG2 137 
#define  MAX98925_LIVE_STATUS0 136 
#define  MAX98925_LIVE_STATUS1 135 
#define  MAX98925_LIVE_STATUS2 134 
#define  MAX98925_REV_VERSION 133 
#define  MAX98925_STATE0 132 
#define  MAX98925_STATE1 131 
#define  MAX98925_STATE2 130 
#define  MAX98925_VBAT_DATA 129 
#define  MAX98925_VBST_DATA 128 

__attribute__((used)) static bool max98925_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX98925_VBAT_DATA:
	case MAX98925_VBST_DATA:
	case MAX98925_LIVE_STATUS0:
	case MAX98925_LIVE_STATUS1:
	case MAX98925_LIVE_STATUS2:
	case MAX98925_STATE0:
	case MAX98925_STATE1:
	case MAX98925_STATE2:
	case MAX98925_FLAG0:
	case MAX98925_FLAG1:
	case MAX98925_FLAG2:
	case MAX98925_REV_VERSION:
		return true;
	default:
		return false;
	}
}