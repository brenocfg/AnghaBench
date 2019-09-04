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
struct dig_thres {int cck_fa_ma; scalar_t__ cur_cck_cca_thres; scalar_t__ pre_cck_cca_thres; } ;
struct phy_dm_struct {struct dig_thres dm_dig_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_CCA ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int /*<<< orphan*/ ,scalar_t__) ; 

void odm_write_cck_cca_thres(void *dm_void, u8 cur_cck_cca_thres)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dig_thres *dig_tab = &dm->dm_dig_table;

	if (dig_tab->cur_cck_cca_thres !=
	    cur_cck_cca_thres) { /* modify by Guo.Mingzhi 2012-01-03 */
		odm_write_1byte(dm, ODM_REG(CCK_CCA, dm), cur_cck_cca_thres);
		dig_tab->cck_fa_ma = 0xffffffff;
	}
	dig_tab->pre_cck_cca_thres = dig_tab->cur_cck_cca_thres;
	dig_tab->cur_cck_cca_thres = cur_cck_cca_thres;
}