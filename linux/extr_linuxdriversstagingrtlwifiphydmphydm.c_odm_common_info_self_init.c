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
typedef  scalar_t__ u8 ;
struct phy_dm_struct {int support_ic_type; int num_rf_path; int tx_rate; int is_init_hw_info_by_rfe; int /*<<< orphan*/  pre_dbg_priority; scalar_t__ nbi_set_result; int /*<<< orphan*/  traffic_load; scalar_t__ total_tp; scalar_t__ rx_tp; scalar_t__ tx_tp; scalar_t__ last_rx_ok_cnt; scalar_t__ last_tx_ok_cnt; scalar_t__ pre_number_active_client; scalar_t__ number_active_client; scalar_t__ pre_number_linked_client; scalar_t__ number_linked_client; scalar_t__ phydm_sys_up_time; int /*<<< orphan*/  phydm_period; scalar_t__ rf_path_rx_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_DBGPORT_RELEASE ; 
 int /*<<< orphan*/  BB_RX_PATH ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int ODM_IC_1SS ; 
 int ODM_IC_2SS ; 
 int ODM_IC_3SS ; 
 int ODM_IC_4SS ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int /*<<< orphan*/  PHYDM_WATCH_DOG_PERIOD ; 
 int /*<<< orphan*/  TRAFFIC_LOW ; 
 scalar_t__ odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_init_mp_driver_status (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_init_cck_setting (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_init_soft_ml_setting (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_init_trx_antenna_setting (struct phy_dm_struct*) ; 

__attribute__((used)) static void odm_common_info_self_init(struct phy_dm_struct *dm)
{
	phydm_init_cck_setting(dm);
	dm->rf_path_rx_enable = (u8)odm_get_bb_reg(dm, ODM_REG(BB_RX_PATH, dm),
						   ODM_BIT(BB_RX_PATH, dm));
	odm_init_mp_driver_status(dm);
	phydm_init_trx_antenna_setting(dm);
	phydm_init_soft_ml_setting(dm);

	dm->phydm_period = PHYDM_WATCH_DOG_PERIOD;
	dm->phydm_sys_up_time = 0;

	if (dm->support_ic_type & ODM_IC_1SS)
		dm->num_rf_path = 1;
	else if (dm->support_ic_type & ODM_IC_2SS)
		dm->num_rf_path = 2;
	else if (dm->support_ic_type & ODM_IC_3SS)
		dm->num_rf_path = 3;
	else if (dm->support_ic_type & ODM_IC_4SS)
		dm->num_rf_path = 4;

	dm->tx_rate = 0xFF;

	dm->number_linked_client = 0;
	dm->pre_number_linked_client = 0;
	dm->number_active_client = 0;
	dm->pre_number_active_client = 0;

	dm->last_tx_ok_cnt = 0;
	dm->last_rx_ok_cnt = 0;
	dm->tx_tp = 0;
	dm->rx_tp = 0;
	dm->total_tp = 0;
	dm->traffic_load = TRAFFIC_LOW;

	dm->nbi_set_result = 0;
	dm->is_init_hw_info_by_rfe = false;
	dm->pre_dbg_priority = BB_DBGPORT_RELEASE;
}