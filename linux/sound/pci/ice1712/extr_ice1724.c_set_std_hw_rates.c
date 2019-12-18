#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* data; } ;
struct snd_ice1712 {int /*<<< orphan*/ * hw_rates; int /*<<< orphan*/  vt1720; TYPE_1__ eeprom; } ;

/* Variables and functions */
 size_t ICE_EEP2_ACLINK ; 
 size_t ICE_EEP2_I2S ; 
 int VT1724_CFG_PRO_I2S ; 
 int /*<<< orphan*/  hw_constraints_rates_192 ; 
 int /*<<< orphan*/  hw_constraints_rates_48 ; 
 int /*<<< orphan*/  hw_constraints_rates_96 ; 

__attribute__((used)) static void set_std_hw_rates(struct snd_ice1712 *ice)
{
	if (ice->eeprom.data[ICE_EEP2_ACLINK] & VT1724_CFG_PRO_I2S) {
		/* I2S */
		/* VT1720 doesn't support more than 96kHz */
		if ((ice->eeprom.data[ICE_EEP2_I2S] & 0x08) && !ice->vt1720)
			ice->hw_rates = &hw_constraints_rates_192;
		else
			ice->hw_rates = &hw_constraints_rates_96;
	} else {
		/* ACLINK */
		ice->hw_rates = &hw_constraints_rates_48;
	}
}