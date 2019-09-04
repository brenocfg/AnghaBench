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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKBYTE3 ; 
 int MASKDWORD ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 

void phy_set_rf_path_switch_8822b(struct phy_dm_struct *dm, bool is_main)
{
	/*BY SY Request */
	odm_set_bb_reg(dm, 0x4C, (BIT(24) | BIT(23)), 0x2);
	odm_set_bb_reg(dm, 0x974, 0xff, 0xff);

	/*odm_set_bb_reg(dm, 0x1991, 0x3, 0x0);*/
	odm_set_bb_reg(dm, 0x1990, (BIT(9) | BIT(8)), 0x0);

	/*odm_set_bb_reg(dm, 0xCBE, 0x8, 0x0);*/
	odm_set_bb_reg(dm, 0xCBC, BIT(19), 0x0);

	odm_set_bb_reg(dm, 0xCB4, 0xff, 0x77);

	odm_set_bb_reg(dm, 0x70, MASKBYTE3, 0x0e);
	odm_set_bb_reg(dm, 0x1704, MASKDWORD, 0x0000ff00);
	odm_set_bb_reg(dm, 0x1700, MASKDWORD, 0xc00f0038);

	if (is_main) {
		/*odm_set_bb_reg(dm, 0xCBD, 0x3, 0x2);		WiFi */
		odm_set_bb_reg(dm, 0xCBC, (BIT(9) | BIT(8)), 0x2); /*WiFi */
	} else {
		/*odm_set_bb_reg(dm, 0xCBD, 0x3, 0x1);	 BT*/
		odm_set_bb_reg(dm, 0xCBC, (BIT(9) | BIT(8)), 0x1); /*BT*/
	}
}