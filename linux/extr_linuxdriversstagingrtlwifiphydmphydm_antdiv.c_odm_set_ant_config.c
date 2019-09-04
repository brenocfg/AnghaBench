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
struct phy_dm_struct {scalar_t__ support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  MASKLWORD ; 
 scalar_t__ ODM_RTL8723B ; 
 scalar_t__ ODM_RTL8723D ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int) ; 

void odm_set_ant_config(void *dm_void, u8 ant_setting /* 0=A, 1=B, 2=C, .... */
			)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type == ODM_RTL8723B) {
		if (ant_setting == 0) /* ant A*/
			odm_set_bb_reg(dm, 0x948, MASKDWORD, 0x00000000);
		else if (ant_setting == 1)
			odm_set_bb_reg(dm, 0x948, MASKDWORD, 0x00000280);
	} else if (dm->support_ic_type == ODM_RTL8723D) {
		if (ant_setting == 0) /* ant A*/
			odm_set_bb_reg(dm, 0x948, MASKLWORD, 0x0000);
		else if (ant_setting == 1)
			odm_set_bb_reg(dm, 0x948, MASKLWORD, 0x0280);
	}
}