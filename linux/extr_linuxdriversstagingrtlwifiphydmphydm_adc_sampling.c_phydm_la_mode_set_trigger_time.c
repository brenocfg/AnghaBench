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
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  odm_set_mac_reg (struct phy_dm_struct*,int,int,int) ; 

void phydm_la_mode_set_trigger_time(void *dm_void, u32 trigger_time_mu_sec)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 trigger_time_unit_num;
	u32 time_unit = 0;

	if (trigger_time_mu_sec < 128)
		time_unit = 0; /*unit: 1mu sec*/
	else if (trigger_time_mu_sec < 256)
		time_unit = 1; /*unit: 2mu sec*/
	else if (trigger_time_mu_sec < 512)
		time_unit = 2; /*unit: 4mu sec*/
	else if (trigger_time_mu_sec < 1024)
		time_unit = 3; /*unit: 8mu sec*/
	else if (trigger_time_mu_sec < 2048)
		time_unit = 4; /*unit: 16mu sec*/
	else if (trigger_time_mu_sec < 4096)
		time_unit = 5; /*unit: 32mu sec*/
	else if (trigger_time_mu_sec < 8192)
		time_unit = 6; /*unit: 64mu sec*/

	trigger_time_unit_num = (u8)(trigger_time_mu_sec >> time_unit);

	ODM_RT_TRACE(
		dm, ODM_COMP_UNCOND,
		"3. [Set Trigger Time] Trig_Time = ((%d)) * unit = ((2^%d us))\n",
		trigger_time_unit_num, time_unit);

	odm_set_mac_reg(dm, 0x7cc, BIT(20) | BIT(19) | BIT(18), time_unit);
	odm_set_mac_reg(dm, 0x7c0, 0x7f00, (trigger_time_unit_num & 0x7f));
}