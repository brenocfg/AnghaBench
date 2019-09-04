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
typedef  int u8 ;
typedef  int u16 ;
struct il_priv {scalar_t__ eeprom; } ;
struct il_channel_info {int channel; } ;
struct il3945_eeprom_txpower_group {int group_channel; } ;
struct il3945_eeprom {struct il3945_eeprom_txpower_group* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_POWER (char*,int,int) ; 
 scalar_t__ il_is_channel_a_band (struct il_channel_info const*) ; 

__attribute__((used)) static u16
il3945_hw_reg_get_ch_grp_idx(struct il_priv *il,
			     const struct il_channel_info *ch_info)
{
	struct il3945_eeprom *eeprom = (struct il3945_eeprom *)il->eeprom;
	struct il3945_eeprom_txpower_group *ch_grp = &eeprom->groups[0];
	u8 group;
	u16 group_idx = 0;	/* based on factory calib frequencies */
	u8 grp_channel;

	/* Find the group idx for the channel ... don't use idx 1(?) */
	if (il_is_channel_a_band(ch_info)) {
		for (group = 1; group < 5; group++) {
			grp_channel = ch_grp[group].group_channel;
			if (ch_info->channel <= grp_channel) {
				group_idx = group;
				break;
			}
		}
		/* group 4 has a few channels *above* its factory cal freq */
		if (group == 5)
			group_idx = 4;
	} else
		group_idx = 0;	/* 2.4 GHz, group 0 */

	D_POWER("Chnl %d mapped to grp %d\n", ch_info->channel, group_idx);
	return group_idx;
}