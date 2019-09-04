#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ phyhang_avoid; TYPE_2__* sh; TYPE_1__ pubpi; } ;
typedef  int s8 ;
typedef  scalar_t__ locomp ;
struct TYPE_4__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CURR_IDX1 ; 
 int /*<<< orphan*/  M_CURR_IDX2 ; 
 int NPHY_TBL_ID_CORE1TXPWRCTL ; 
 int NPHY_TBL_ID_CORE2TXPWRCTL ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int* nphy_tpc_loscale ; 
 int /*<<< orphan*/  wlapi_bmac_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int,int,int,int,int*) ; 

__attribute__((used)) static void wlc_phy_txpwrctrl_coeff_setup_nphy(struct brcms_phy *pi)
{
	u32 idx;
	u16 iqloCalbuf[7];
	u32 iqcomp, locomp, curr_locomp;
	s8 locomp_i, locomp_q;
	s8 curr_locomp_i, curr_locomp_q;
	u32 tbl_id, tbl_len, tbl_offset;
	u32 regval[128];

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, true);

	wlc_phy_table_read_nphy(pi, 15, 7, 80, 16, iqloCalbuf);

	tbl_len = 128;
	tbl_offset = 320;
	for (tbl_id = NPHY_TBL_ID_CORE1TXPWRCTL;
	     tbl_id <= NPHY_TBL_ID_CORE2TXPWRCTL; tbl_id++) {
		iqcomp =
			(tbl_id ==
			 26) ? (((u32) (iqloCalbuf[0] & 0x3ff)) << 10) |
			(iqloCalbuf[1] & 0x3ff)
			: (((u32) (iqloCalbuf[2] & 0x3ff)) << 10) |
			(iqloCalbuf[3] & 0x3ff);

		for (idx = 0; idx < tbl_len; idx++)
			regval[idx] = iqcomp;
		wlc_phy_table_write_nphy(pi, tbl_id, tbl_len, tbl_offset, 32,
					 regval);
	}

	tbl_offset = 448;
	for (tbl_id = NPHY_TBL_ID_CORE1TXPWRCTL;
	     tbl_id <= NPHY_TBL_ID_CORE2TXPWRCTL; tbl_id++) {

		locomp =
			(u32) ((tbl_id == 26) ? iqloCalbuf[5] : iqloCalbuf[6]);
		locomp_i = (s8) ((locomp >> 8) & 0xff);
		locomp_q = (s8) ((locomp) & 0xff);
		for (idx = 0; idx < tbl_len; idx++) {
			if (NREV_GE(pi->pubpi.phy_rev, 3)) {
				curr_locomp_i = locomp_i;
				curr_locomp_q = locomp_q;
			} else {
				curr_locomp_i = (s8) ((locomp_i *
						       nphy_tpc_loscale[idx] +
						       128) >> 8);
				curr_locomp_q =
					(s8) ((locomp_q *
					       nphy_tpc_loscale[idx] +
					       128) >> 8);
			}
			curr_locomp = (u32) ((curr_locomp_i & 0xff) << 8);
			curr_locomp |= (u32) (curr_locomp_q & 0xff);
			regval[idx] = curr_locomp;
		}
		wlc_phy_table_write_nphy(pi, tbl_id, tbl_len, tbl_offset, 32,
					 regval);
	}

	if (NREV_LT(pi->pubpi.phy_rev, 2)) {

		wlapi_bmac_write_shm(pi->sh->physhim, M_CURR_IDX1, 0xFFFF);
		wlapi_bmac_write_shm(pi->sh->physhim, M_CURR_IDX2, 0xFFFF);
	}

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, false);
}