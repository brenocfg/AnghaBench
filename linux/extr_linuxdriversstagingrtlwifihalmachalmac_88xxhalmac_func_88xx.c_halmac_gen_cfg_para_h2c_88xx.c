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
typedef  int /*<<< orphan*/  u8 ;
struct halmac_config_para_info {scalar_t__ full_fifo_mode; int /*<<< orphan*/  para_num; } ;
struct TYPE_2__ {scalar_t__ rsvd_pg_bndy; scalar_t__ rsvd_h2c_extra_info_pg_bndy; } ;
struct halmac_adapter {TYPE_1__ txff_allocation; struct halmac_config_para_info config_para_info; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_PARAMETER_SET_INIT_CASE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CFG_PARAMETER_SET_NUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_PARAMETER_SET_PHY_PARAMETER_LOC (int /*<<< orphan*/ *,scalar_t__) ; 
 int HALMAC_RET_SUCCESS ; 

__attribute__((used)) static enum halmac_ret_status
halmac_gen_cfg_para_h2c_88xx(struct halmac_adapter *halmac_adapter,
			     u8 *h2c_buff)
{
	struct halmac_config_para_info *config_para_info =
		&halmac_adapter->config_para_info;

	CFG_PARAMETER_SET_NUM(h2c_buff, config_para_info->para_num);

	if (config_para_info->full_fifo_mode) {
		CFG_PARAMETER_SET_INIT_CASE(h2c_buff, 0x1);
		CFG_PARAMETER_SET_PHY_PARAMETER_LOC(h2c_buff, 0);
	} else {
		CFG_PARAMETER_SET_INIT_CASE(h2c_buff, 0x0);
		CFG_PARAMETER_SET_PHY_PARAMETER_LOC(
			h2c_buff,
			halmac_adapter->txff_allocation
					.rsvd_h2c_extra_info_pg_bndy -
				halmac_adapter->txff_allocation.rsvd_pg_bndy);
	}

	return HALMAC_RET_SUCCESS;
}