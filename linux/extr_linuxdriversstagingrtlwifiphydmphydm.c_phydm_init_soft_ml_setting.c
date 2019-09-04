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
struct phy_dm_struct {int support_ic_type; int /*<<< orphan*/  mp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phydm_init_soft_ml_setting(struct phy_dm_struct *dm)
{
	if (!dm->mp_mode) {
		if (dm->support_ic_type & ODM_RTL8822B)
			odm_set_bb_reg(dm, 0x19a8, MASKDWORD, 0xc10a0000);
	}
}