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
typedef  size_t u8 ;
struct dm_iqk_info {int rxiqk_step; int*** gs_retry_count; int** rxiqk_fail_code; int isbnd; int*** retry_count; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;

/* Variables and functions */
 size_t GSRXK1 ; 
 size_t GSRXK2 ; 
 size_t RXIQK1 ; 
 size_t RXIQK2 ; 
 int _iqk_one_shot_8822b (struct phy_dm_struct*,size_t,size_t) ; 
 int _iqk_rx_iqk_gain_search_fail_8822b (struct phy_dm_struct*,size_t,size_t) ; 
 int /*<<< orphan*/  _iqk_rxk1_setting_8822b (struct phy_dm_struct*,size_t) ; 
 int /*<<< orphan*/  _iqk_rxk2_setting_8822b (struct phy_dm_struct*,size_t,int) ; 
 int rxiqk_gs_limit ; 

__attribute__((used)) static bool _iqk_rx_iqk_by_path_8822b(void *dm_void, u8 path)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	bool KFAIL = true, gonext;

	switch (iqk_info->rxiqk_step) {
	case 1: /*gain search_RXK1*/
		_iqk_rxk1_setting_8822b(dm, path);
		gonext = false;
		while (1) {
			KFAIL = _iqk_rx_iqk_gain_search_fail_8822b(dm, path,
								   RXIQK1);
			if (KFAIL &&
			    (iqk_info->gs_retry_count[0][path][GSRXK1] < 2))
				iqk_info->gs_retry_count[0][path][GSRXK1]++;
			else if (KFAIL) {
				iqk_info->rxiqk_fail_code[0][path] = 0;
				iqk_info->rxiqk_step = 5;
				gonext = true;
			} else {
				iqk_info->rxiqk_step++;
				gonext = true;
			}
			if (gonext)
				break;
		}
		break;
	case 2: /*gain search_RXK2*/
		_iqk_rxk2_setting_8822b(dm, path, true);
		iqk_info->isbnd = false;
		while (1) {
			KFAIL = _iqk_rx_iqk_gain_search_fail_8822b(dm, path,
								   RXIQK2);
			if (KFAIL &&
			    (iqk_info->gs_retry_count[0][path][GSRXK2] <
			     rxiqk_gs_limit)) {
				iqk_info->gs_retry_count[0][path][GSRXK2]++;
			} else {
				iqk_info->rxiqk_step++;
				break;
			}
		}
		break;
	case 3: /*RXK1*/
		_iqk_rxk1_setting_8822b(dm, path);
		gonext = false;
		while (1) {
			KFAIL = _iqk_one_shot_8822b(dm, path, RXIQK1);
			if (KFAIL &&
			    (iqk_info->retry_count[0][path][RXIQK1] < 2))
				iqk_info->retry_count[0][path][RXIQK1]++;
			else if (KFAIL) {
				iqk_info->rxiqk_fail_code[0][path] = 1;
				iqk_info->rxiqk_step = 5;
				gonext = true;
			} else {
				iqk_info->rxiqk_step++;
				gonext = true;
			}
			if (gonext)
				break;
		}
		break;
	case 4: /*RXK2*/
		_iqk_rxk2_setting_8822b(dm, path, false);
		gonext = false;
		while (1) {
			KFAIL = _iqk_one_shot_8822b(dm, path, RXIQK2);
			if (KFAIL &&
			    (iqk_info->retry_count[0][path][RXIQK2] < 2))
				iqk_info->retry_count[0][path][RXIQK2]++;
			else if (KFAIL) {
				iqk_info->rxiqk_fail_code[0][path] = 2;
				iqk_info->rxiqk_step = 5;
				gonext = true;
			} else {
				iqk_info->rxiqk_step++;
				gonext = true;
			}
			if (gonext)
				break;
		}
		break;
	}
	return KFAIL;
}