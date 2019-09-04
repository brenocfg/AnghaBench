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
typedef  scalar_t__ u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 scalar_t__ AUX_ANT ; 
 int BIT (int) ; 
 scalar_t__ MAIN_ANT ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int ODM_RTL8821 ; 
 int ODM_RTL8881A ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_set_mac_reg (struct phy_dm_struct*,int,int,int) ; 

void phydm_set_ext_switch(void *dm_void, u32 *const dm_value, u32 *_used,
			  char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 ext_ant_switch = dm_value[0];

	if (dm->support_ic_type & (ODM_RTL8821 | ODM_RTL8881A)) {
		/*Output Pin Settings*/
		odm_set_mac_reg(dm, 0x4C, BIT(23),
				0); /*select DPDT_P and DPDT_N as output pin*/
		odm_set_mac_reg(dm, 0x4C, BIT(24), 1); /*by WLAN control*/

		odm_set_bb_reg(dm, 0xCB4, 0xF, 7); /*DPDT_P = 1b'0*/
		odm_set_bb_reg(dm, 0xCB4, 0xF0, 7); /*DPDT_N = 1b'0*/

		if (ext_ant_switch == MAIN_ANT) {
			odm_set_bb_reg(dm, 0xCB4, (BIT(29) | BIT(28)), 1);
			ODM_RT_TRACE(
				dm, ODM_COMP_API,
				"***8821A set ant switch = 2b'01 (Main)\n");
		} else if (ext_ant_switch == AUX_ANT) {
			odm_set_bb_reg(dm, 0xCB4, BIT(29) | BIT(28), 2);
			ODM_RT_TRACE(dm, ODM_COMP_API,
				     "***8821A set ant switch = 2b'10 (Aux)\n");
		}
	}
}