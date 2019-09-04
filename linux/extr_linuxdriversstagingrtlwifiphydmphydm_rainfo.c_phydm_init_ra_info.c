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
struct phy_dm_struct {scalar_t__ support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  MASKBYTE3 ; 
 scalar_t__ ODM_RTL8822B ; 
 scalar_t__ odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,scalar_t__) ; 

void phydm_init_ra_info(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type == ODM_RTL8822B) {
		u32 ret_value;

		ret_value = odm_get_bb_reg(dm, 0x4c8, MASKBYTE2);
		odm_set_bb_reg(dm, 0x4cc, MASKBYTE3, (ret_value - 1));
	}
}