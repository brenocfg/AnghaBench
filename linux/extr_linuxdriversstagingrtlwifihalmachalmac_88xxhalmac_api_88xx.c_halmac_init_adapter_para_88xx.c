#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_11__ {int /*<<< orphan*/  rx_fifo_expanding_mode; int /*<<< orphan*/  la_mode; scalar_t__ extra_queue_pg_num; scalar_t__ normal_queue_pg_num; scalar_t__ low_queue_pg_num; scalar_t__ high_queue_pg_num; scalar_t__ pub_queue_pg_num; scalar_t__ rsvd_fw_txbuff_pg_bndy; scalar_t__ rsvd_cpu_instr_pg_bndy; scalar_t__ rsvd_h2c_queue_pg_bndy; scalar_t__ rsvd_h2c_extra_info_pg_bndy; scalar_t__ rsvd_drv_pg_bndy; scalar_t__ rsvd_pg_bndy; scalar_t__ ac_q_pg_num; scalar_t__ tx_fifo_pg_num; } ;
struct TYPE_12__ {int /*<<< orphan*/  api_array; scalar_t__ array_wptr; } ;
struct TYPE_10__ {scalar_t__ ch_num; scalar_t__ total_size; scalar_t__ avai_buf_size; scalar_t__ buf_size; scalar_t__ extra_info_en; int /*<<< orphan*/ * ch_info_buf_w; int /*<<< orphan*/ * ch_info_buf; } ;
struct TYPE_18__ {int full_fifo_mode; scalar_t__ datapack_segment; scalar_t__ value_accumulation; scalar_t__ offset_accumulation; scalar_t__ avai_para_buf_size; scalar_t__ para_buf_size; scalar_t__ para_num; int /*<<< orphan*/ * para_buf_w; int /*<<< orphan*/ * cfg_para_buf; } ;
struct TYPE_17__ {int mode; int awake_interval; int enter_32K; int adopt_user_setting; scalar_t__ drv_bcn_early_shift; scalar_t__ two_antenna_en; scalar_t__ fast_bt_connect; scalar_t__ silence_period; scalar_t__ protect_bcn; scalar_t__ ps_allow_bt_high_priority; scalar_t__ ant_auto_switch; scalar_t__ low_pwr_rx_beacon; scalar_t__ pwr_state; scalar_t__ all_queue_uapsd; scalar_t__ smart_ps; scalar_t__ rlbm; scalar_t__ clk_request; } ;
struct halmac_adapter {int hal_efuse_map_valid; int low_clk; TYPE_2__ txff_allocation; TYPE_3__ api_record; scalar_t__ drv_info_size; TYPE_1__ ch_sw_info; TYPE_9__ config_para_info; TYPE_8__ fwlps_option; int /*<<< orphan*/  max_download_size; TYPE_7__* hal_bss_addr; TYPE_5__* hal_mac_addr; scalar_t__ efuse_end; int /*<<< orphan*/ * hal_efuse_map; struct halmac_adapter* hal_adapter_backup; } ;
struct TYPE_15__ {scalar_t__ address_high; scalar_t__ address_low; } ;
struct TYPE_16__ {TYPE_6__ address_l_h; } ;
struct TYPE_13__ {scalar_t__ address_high; scalar_t__ address_low; } ;
struct TYPE_14__ {TYPE_4__ address_l_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_API_STUFF ; 
 int /*<<< orphan*/  HALMAC_FW_MAX_DL_SIZE_88XX ; 
 int /*<<< orphan*/  HALMAC_LA_MODE_DISABLE ; 
 int /*<<< orphan*/  HALMAC_RX_FIFO_EXPANDING_MODE_DISABLE ; 
 int /*<<< orphan*/  halmac_init_adapter_dynamic_para_88xx (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_init_state_machine_88xx (struct halmac_adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void halmac_init_adapter_para_88xx(struct halmac_adapter *halmac_adapter)
{
	halmac_adapter->api_record.array_wptr = 0;
	halmac_adapter->hal_adapter_backup = halmac_adapter;
	halmac_adapter->hal_efuse_map = (u8 *)NULL;
	halmac_adapter->hal_efuse_map_valid = false;
	halmac_adapter->efuse_end = 0;
	halmac_adapter->hal_mac_addr[0].address_l_h.address_low = 0;
	halmac_adapter->hal_mac_addr[0].address_l_h.address_high = 0;
	halmac_adapter->hal_mac_addr[1].address_l_h.address_low = 0;
	halmac_adapter->hal_mac_addr[1].address_l_h.address_high = 0;
	halmac_adapter->hal_bss_addr[0].address_l_h.address_low = 0;
	halmac_adapter->hal_bss_addr[0].address_l_h.address_high = 0;
	halmac_adapter->hal_bss_addr[1].address_l_h.address_low = 0;
	halmac_adapter->hal_bss_addr[1].address_l_h.address_high = 0;

	halmac_adapter->low_clk = false;
	halmac_adapter->max_download_size = HALMAC_FW_MAX_DL_SIZE_88XX;

	/* Init LPS Option */
	halmac_adapter->fwlps_option.mode = 0x01; /*0:Active 1:LPS 2:WMMPS*/
	halmac_adapter->fwlps_option.awake_interval = 1;
	halmac_adapter->fwlps_option.enter_32K = 1;
	halmac_adapter->fwlps_option.clk_request = 0;
	halmac_adapter->fwlps_option.rlbm = 0;
	halmac_adapter->fwlps_option.smart_ps = 0;
	halmac_adapter->fwlps_option.awake_interval = 1;
	halmac_adapter->fwlps_option.all_queue_uapsd = 0;
	halmac_adapter->fwlps_option.pwr_state = 0;
	halmac_adapter->fwlps_option.low_pwr_rx_beacon = 0;
	halmac_adapter->fwlps_option.ant_auto_switch = 0;
	halmac_adapter->fwlps_option.ps_allow_bt_high_priority = 0;
	halmac_adapter->fwlps_option.protect_bcn = 0;
	halmac_adapter->fwlps_option.silence_period = 0;
	halmac_adapter->fwlps_option.fast_bt_connect = 0;
	halmac_adapter->fwlps_option.two_antenna_en = 0;
	halmac_adapter->fwlps_option.adopt_user_setting = 1;
	halmac_adapter->fwlps_option.drv_bcn_early_shift = 0;

	halmac_adapter->config_para_info.cfg_para_buf = NULL;
	halmac_adapter->config_para_info.para_buf_w = NULL;
	halmac_adapter->config_para_info.para_num = 0;
	halmac_adapter->config_para_info.full_fifo_mode = false;
	halmac_adapter->config_para_info.para_buf_size = 0;
	halmac_adapter->config_para_info.avai_para_buf_size = 0;
	halmac_adapter->config_para_info.offset_accumulation = 0;
	halmac_adapter->config_para_info.value_accumulation = 0;
	halmac_adapter->config_para_info.datapack_segment = 0;

	halmac_adapter->ch_sw_info.ch_info_buf = NULL;
	halmac_adapter->ch_sw_info.ch_info_buf_w = NULL;
	halmac_adapter->ch_sw_info.extra_info_en = 0;
	halmac_adapter->ch_sw_info.buf_size = 0;
	halmac_adapter->ch_sw_info.avai_buf_size = 0;
	halmac_adapter->ch_sw_info.total_size = 0;
	halmac_adapter->ch_sw_info.ch_num = 0;

	halmac_adapter->drv_info_size = 0;

	memset(halmac_adapter->api_record.api_array, HALMAC_API_STUFF,
	       sizeof(halmac_adapter->api_record.api_array));

	halmac_adapter->txff_allocation.tx_fifo_pg_num = 0;
	halmac_adapter->txff_allocation.ac_q_pg_num = 0;
	halmac_adapter->txff_allocation.rsvd_pg_bndy = 0;
	halmac_adapter->txff_allocation.rsvd_drv_pg_bndy = 0;
	halmac_adapter->txff_allocation.rsvd_h2c_extra_info_pg_bndy = 0;
	halmac_adapter->txff_allocation.rsvd_h2c_queue_pg_bndy = 0;
	halmac_adapter->txff_allocation.rsvd_cpu_instr_pg_bndy = 0;
	halmac_adapter->txff_allocation.rsvd_fw_txbuff_pg_bndy = 0;
	halmac_adapter->txff_allocation.pub_queue_pg_num = 0;
	halmac_adapter->txff_allocation.high_queue_pg_num = 0;
	halmac_adapter->txff_allocation.low_queue_pg_num = 0;
	halmac_adapter->txff_allocation.normal_queue_pg_num = 0;
	halmac_adapter->txff_allocation.extra_queue_pg_num = 0;

	halmac_adapter->txff_allocation.la_mode = HALMAC_LA_MODE_DISABLE;
	halmac_adapter->txff_allocation.rx_fifo_expanding_mode =
		HALMAC_RX_FIFO_EXPANDING_MODE_DISABLE;

	halmac_init_adapter_dynamic_para_88xx(halmac_adapter);
	halmac_init_state_machine_88xx(halmac_adapter);
}