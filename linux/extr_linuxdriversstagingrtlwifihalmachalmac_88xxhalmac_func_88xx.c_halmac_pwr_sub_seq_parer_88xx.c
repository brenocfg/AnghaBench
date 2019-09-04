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
struct halmac_wl_pwr_cfg_ {int interface_msk; int fab_msk; int cut_msk; } ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_SUCCESS ; 
 int halmac_pwr_sub_seq_parer_do_cmd_88xx (struct halmac_adapter*,struct halmac_wl_pwr_cfg_*,int*) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_pwr_sub_seq_parer_88xx(struct halmac_adapter *halmac_adapter, u8 cut,
			      u8 fab, u8 intf,
			      struct halmac_wl_pwr_cfg_ *pwr_sub_seq_cfg)
{
	struct halmac_wl_pwr_cfg_ *sub_seq_cmd;
	bool reti;
	enum halmac_ret_status status;

	for (sub_seq_cmd = pwr_sub_seq_cfg;; sub_seq_cmd++) {
		if ((sub_seq_cmd->interface_msk & intf) &&
		    (sub_seq_cmd->fab_msk & fab) &&
		    (sub_seq_cmd->cut_msk & cut)) {
			status = halmac_pwr_sub_seq_parer_do_cmd_88xx(
				halmac_adapter, sub_seq_cmd, &reti);

			if (reti)
				return status;
		}
	}

	return HALMAC_RET_SUCCESS;
}