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
struct dyn_pwr_saving {int initialize; int reg874; int regc70; int reg85c; int rega74; scalar_t__ pre_rf_state; scalar_t__ cur_rf_state; } ;
struct phy_dm_struct {int patch_id; struct dyn_pwr_saving dm_ps_table; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  phydm_update_rf_state (struct phy_dm_struct*,struct dyn_pwr_saving*,int,int,int) ; 
 scalar_t__ rf_save ; 

void odm_rf_saving(void *dm_void, u8 is_force_in_normal)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dyn_pwr_saving *dm_ps_table = &dm->dm_ps_table;
	u8 rssi_up_bound = 30;
	u8 rssi_low_bound = 25;

	if (dm->patch_id == 40) { /* RT_CID_819x_FUNAI_TV */
		rssi_up_bound = 50;
		rssi_low_bound = 45;
	}
	if (dm_ps_table->initialize == 0) {
		dm_ps_table->reg874 =
			(odm_get_bb_reg(dm, 0x874, MASKDWORD) & 0x1CC000) >> 14;
		dm_ps_table->regc70 =
			(odm_get_bb_reg(dm, 0xc70, MASKDWORD) & BIT(3)) >> 3;
		dm_ps_table->reg85c =
			(odm_get_bb_reg(dm, 0x85c, MASKDWORD) & 0xFF000000) >>
			24;
		dm_ps_table->rega74 =
			(odm_get_bb_reg(dm, 0xa74, MASKDWORD) & 0xF000) >> 12;
		/* Reg818 = phy_query_bb_reg(adapter, 0x818, MASKDWORD); */
		dm_ps_table->initialize = 1;
	}

	phydm_update_rf_state(dm, dm_ps_table, rssi_up_bound, rssi_low_bound,
			      is_force_in_normal);

	if (dm_ps_table->pre_rf_state != dm_ps_table->cur_rf_state) {
		if (dm_ps_table->cur_rf_state == rf_save) {
			odm_set_bb_reg(dm, 0x874, 0x1C0000,
				       0x2); /* reg874[20:18]=3'b010 */
			odm_set_bb_reg(dm, 0xc70, BIT(3),
				       0); /* regc70[3]=1'b0 */
			odm_set_bb_reg(dm, 0x85c, 0xFF000000,
				       0x63); /* reg85c[31:24]=0x63 */
			odm_set_bb_reg(dm, 0x874, 0xC000,
				       0x2); /* reg874[15:14]=2'b10 */
			odm_set_bb_reg(dm, 0xa74, 0xF000,
				       0x3); /* RegA75[7:4]=0x3 */
			odm_set_bb_reg(dm, 0x818, BIT(28),
				       0x0); /* Reg818[28]=1'b0 */
			odm_set_bb_reg(dm, 0x818, BIT(28),
				       0x1); /* Reg818[28]=1'b1 */
		} else {
			odm_set_bb_reg(dm, 0x874, 0x1CC000,
				       dm_ps_table->reg874);
			odm_set_bb_reg(dm, 0xc70, BIT(3), dm_ps_table->regc70);
			odm_set_bb_reg(dm, 0x85c, 0xFF000000,
				       dm_ps_table->reg85c);
			odm_set_bb_reg(dm, 0xa74, 0xF000, dm_ps_table->rega74);
			odm_set_bb_reg(dm, 0x818, BIT(28), 0x0);
		}
		dm_ps_table->pre_rf_state = dm_ps_table->cur_rf_state;
	}
}