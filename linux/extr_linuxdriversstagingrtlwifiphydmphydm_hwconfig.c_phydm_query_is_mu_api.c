#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_2__ {size_t* num_of_ppdu; size_t* gid_num; } ;
struct phy_dm_struct {TYPE_1__ phy_dbg_info; } ;

/* Variables and functions */
 size_t BIT (int) ; 

bool phydm_query_is_mu_api(struct phy_dm_struct *phydm, u8 ppdu_idx,
			   u8 *p_data_rate, u8 *p_gid)
{
	u8 data_rate = 0, gid = 0;
	bool is_mu = false;

	data_rate = phydm->phy_dbg_info.num_of_ppdu[ppdu_idx];
	gid = phydm->phy_dbg_info.gid_num[ppdu_idx];

	if (data_rate & BIT(7)) {
		is_mu = true;
		data_rate = data_rate & ~(BIT(7));
	} else {
		is_mu = false;
	}

	*p_data_rate = data_rate;
	*p_gid = gid;

	return is_mu;
}