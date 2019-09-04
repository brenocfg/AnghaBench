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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ath5k_eeprom_info {int* ee_switch_settling; int* ee_atn_tx_rx; int** ee_ant_control; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {int** ah_ant_ctl; TYPE_1__ ah_capabilities; } ;

/* Variables and functions */
 size_t AR5K_ANT_CTL ; 
 size_t AR5K_ANT_SWTABLE_A ; 
 size_t AR5K_ANT_SWTABLE_B ; 
 int /*<<< orphan*/  AR5K_EEPROM_READ (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath5k_eeprom_read_ants(struct ath5k_hw *ah, u32 *offset,
		unsigned int mode)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 o = *offset;
	u16 val;
	int i = 0;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_switch_settling[mode]	= (val >> 8) & 0x7f;
	ee->ee_atn_tx_rx[mode]		= (val >> 2) & 0x3f;
	ee->ee_ant_control[mode][i]	= (val << 4) & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	|= (val >> 12) & 0xf;
	ee->ee_ant_control[mode][i++]	= (val >> 6) & 0x3f;
	ee->ee_ant_control[mode][i++]	= val & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	= (val >> 10) & 0x3f;
	ee->ee_ant_control[mode][i++]	= (val >> 4) & 0x3f;
	ee->ee_ant_control[mode][i]	= (val << 2) & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	|= (val >> 14) & 0x3;
	ee->ee_ant_control[mode][i++]	= (val >> 8) & 0x3f;
	ee->ee_ant_control[mode][i++]	= (val >> 2) & 0x3f;
	ee->ee_ant_control[mode][i]	= (val << 4) & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	|= (val >> 12) & 0xf;
	ee->ee_ant_control[mode][i++]	= (val >> 6) & 0x3f;
	ee->ee_ant_control[mode][i++]	= val & 0x3f;

	/* Get antenna switch tables */
	ah->ah_ant_ctl[mode][AR5K_ANT_CTL] =
	    (ee->ee_ant_control[mode][0] << 4);
	ah->ah_ant_ctl[mode][AR5K_ANT_SWTABLE_A] =
	     ee->ee_ant_control[mode][1]	|
	    (ee->ee_ant_control[mode][2] << 6)	|
	    (ee->ee_ant_control[mode][3] << 12) |
	    (ee->ee_ant_control[mode][4] << 18) |
	    (ee->ee_ant_control[mode][5] << 24);
	ah->ah_ant_ctl[mode][AR5K_ANT_SWTABLE_B] =
	     ee->ee_ant_control[mode][6]	|
	    (ee->ee_ant_control[mode][7] << 6)	|
	    (ee->ee_ant_control[mode][8] << 12) |
	    (ee->ee_ant_control[mode][9] << 18) |
	    (ee->ee_ant_control[mode][10] << 24);

	/* return new offset */
	*offset = o;

	return 0;
}