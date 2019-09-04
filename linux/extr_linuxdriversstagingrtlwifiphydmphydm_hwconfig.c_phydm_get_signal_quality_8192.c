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
struct phy_status_rpt_8192cd {int cck_sig_qual_ofdm_pwdb_all; } ;
struct phy_dm_struct {int /*<<< orphan*/  is_in_hct_test; } ;
struct dm_phy_status_info {int rx_pwdb_all; } ;

/* Variables and functions */

__attribute__((used)) static inline u8
phydm_get_signal_quality_8192(struct dm_phy_status_info *phy_info,
			      struct phy_dm_struct *dm,
			      struct phy_status_rpt_8192cd *phy_sta_rpt)
{
	u8 sq_rpt;

	if (phy_info->rx_pwdb_all > 40 && !dm->is_in_hct_test)
		return 100;

	sq_rpt = phy_sta_rpt->cck_sig_qual_ofdm_pwdb_all;

	if (sq_rpt > 64)
		return 0;
	else if (sq_rpt < 20)
		return 100;
	else
		return ((64 - sq_rpt) * 100) / 44;
}