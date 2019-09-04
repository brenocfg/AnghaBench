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
struct rtsx_chip {int adma_mode; int driver_first_load; int mspro_formatter_enable; int ss_idle_period; int dynamic_aspm; int asic_sd_sdr104_clk; int asic_sd_sdr50_clk; int asic_sd_ddr50_clk; int asic_sd_hs_clk; int asic_mmc_52m_clk; int asic_ms_hg_clk; int asic_ms_4bit_clk; int asic_ms_1bit_clk; int ssc_en; int sd_speed_prior; int sd_current_prior; int sd_ctl; int mmc_ddr_tx_phase; int sd_default_tx_phase; int sd_default_rx_phase; int pmos_pwr_on_interval; int sd_voltage_switch_delay; int ms_power_class_en; int sd_400mA_ocp_thd; int sd_800mA_ocp_thd; int ms_ocp_thd; int card_drive_sel; int sd30_drive_sel_1v8; int sd30_drive_sel_3v3; int do_delink_before_power_down; int auto_power_down; int force_clkreq_0; int sdio_retry_cnt; int xd_timeout; int sd_timeout; int ms_timeout; int mspro_timeout; int power_down_in_ss; int sdr104_en; int sdr50_en; int ddr50_en; int delink_stage1_step; int delink_stage2_step; int delink_stage3_step; int auto_delink_in_L1; int blink_led; int support_ms_8bit; int s3_pwr_off_delay; scalar_t__ phy_voltage; scalar_t__ max_payload; scalar_t__ hp_watch_bios_hotplug; int /*<<< orphan*/  msi_en; scalar_t__ ft2_fast_mode; scalar_t__ polling_config; scalar_t__ sd_ddr_tx_phase; void* ssc_depth_low_speed; void* ssc_depth_ms_4bit; void* ssc_depth_ms_hg; void* ssc_depth_mmc_52m; void* ssc_depth_sd_hs; void* ssc_depth_sd_ddr50; void* ssc_depth_sd_sdr50; void* ssc_depth_sd_sdr104; int /*<<< orphan*/  fpga_ms_1bit_clk; void* fpga_ms_4bit_clk; void* fpga_ms_hg_clk; void* fpga_mmc_52m_clk; void* fpga_sd_hs_clk; void* fpga_sd_sdr50_clk; void* fpga_sd_ddr50_clk; int /*<<< orphan*/  fpga_sd_sdr104_clk; int /*<<< orphan*/  aspm_l0s_l1_en; scalar_t__ remote_wakeup_en; int /*<<< orphan*/  ss_en; int /*<<< orphan*/  auto_delink_en; int /*<<< orphan*/  lun_mode; scalar_t__ use_hw_setting; scalar_t__ ignore_sd; scalar_t__ lun_mc; TYPE_2__* rtsx; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_4__ {TYPE_1__* pci; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 void* CLK_100 ; 
 int /*<<< orphan*/  CLK_200 ; 
 int /*<<< orphan*/  CLK_40 ; 
 void* CLK_80 ; 
 int /*<<< orphan*/  DEFAULT_SINGLE ; 
 int SD_PUSH_POINT_AUTO ; 
 int SD_SAMPLE_POINT_AUTO ; 
 void* SSC_DEPTH_1M ; 
 void* SSC_DEPTH_2M ; 
 void* SSC_DEPTH_512K ; 
 int SUPPORT_MMC_DDR_MODE ; 
 int /*<<< orphan*/  aspm_l0s_l1_en ; 
 int /*<<< orphan*/  auto_delink_en ; 
 int /*<<< orphan*/  msi_en ; 
 int /*<<< orphan*/  ss_en ; 
 int ss_interval ; 

__attribute__((used)) static void rtsx_init_options(struct rtsx_chip *chip)
{
	chip->vendor_id = chip->rtsx->pci->vendor;
	chip->product_id = chip->rtsx->pci->device;
	chip->adma_mode = 1;
	chip->lun_mc = 0;
	chip->driver_first_load = 1;
#ifdef HW_AUTO_SWITCH_SD_BUS
	chip->sdio_in_charge = 0;
#endif

	chip->mspro_formatter_enable = 1;
	chip->ignore_sd = 0;
	chip->use_hw_setting = 0;
	chip->lun_mode = DEFAULT_SINGLE;
	chip->auto_delink_en = auto_delink_en;
	chip->ss_en = ss_en;
	chip->ss_idle_period = ss_interval * 1000;
	chip->remote_wakeup_en = 0;
	chip->aspm_l0s_l1_en = aspm_l0s_l1_en;
	chip->dynamic_aspm = 1;
	chip->fpga_sd_sdr104_clk = CLK_200;
	chip->fpga_sd_ddr50_clk = CLK_100;
	chip->fpga_sd_sdr50_clk = CLK_100;
	chip->fpga_sd_hs_clk = CLK_100;
	chip->fpga_mmc_52m_clk = CLK_80;
	chip->fpga_ms_hg_clk = CLK_80;
	chip->fpga_ms_4bit_clk = CLK_80;
	chip->fpga_ms_1bit_clk = CLK_40;
	chip->asic_sd_sdr104_clk = 203;
	chip->asic_sd_sdr50_clk = 98;
	chip->asic_sd_ddr50_clk = 98;
	chip->asic_sd_hs_clk = 98;
	chip->asic_mmc_52m_clk = 98;
	chip->asic_ms_hg_clk = 117;
	chip->asic_ms_4bit_clk = 78;
	chip->asic_ms_1bit_clk = 39;
	chip->ssc_depth_sd_sdr104 = SSC_DEPTH_2M;
	chip->ssc_depth_sd_sdr50 = SSC_DEPTH_2M;
	chip->ssc_depth_sd_ddr50 = SSC_DEPTH_1M;
	chip->ssc_depth_sd_hs = SSC_DEPTH_1M;
	chip->ssc_depth_mmc_52m = SSC_DEPTH_1M;
	chip->ssc_depth_ms_hg = SSC_DEPTH_1M;
	chip->ssc_depth_ms_4bit = SSC_DEPTH_512K;
	chip->ssc_depth_low_speed = SSC_DEPTH_512K;
	chip->ssc_en = 1;
	chip->sd_speed_prior = 0x01040203;
	chip->sd_current_prior = 0x00010203;
	chip->sd_ctl = SD_PUSH_POINT_AUTO |
		       SD_SAMPLE_POINT_AUTO |
		       SUPPORT_MMC_DDR_MODE;
	chip->sd_ddr_tx_phase = 0;
	chip->mmc_ddr_tx_phase = 1;
	chip->sd_default_tx_phase = 15;
	chip->sd_default_rx_phase = 15;
	chip->pmos_pwr_on_interval = 200;
	chip->sd_voltage_switch_delay = 1000;
	chip->ms_power_class_en = 3;

	chip->sd_400mA_ocp_thd = 1;
	chip->sd_800mA_ocp_thd = 5;
	chip->ms_ocp_thd = 2;

	chip->card_drive_sel = 0x55;
	chip->sd30_drive_sel_1v8 = 0x03;
	chip->sd30_drive_sel_3v3 = 0x01;

	chip->do_delink_before_power_down = 1;
	chip->auto_power_down = 1;
	chip->polling_config = 0;

	chip->force_clkreq_0 = 1;
	chip->ft2_fast_mode = 0;

	chip->sdio_retry_cnt = 1;

	chip->xd_timeout = 2000;
	chip->sd_timeout = 10000;
	chip->ms_timeout = 2000;
	chip->mspro_timeout = 15000;

	chip->power_down_in_ss = 1;

	chip->sdr104_en = 1;
	chip->sdr50_en = 1;
	chip->ddr50_en = 1;

	chip->delink_stage1_step = 100;
	chip->delink_stage2_step = 40;
	chip->delink_stage3_step = 20;

	chip->auto_delink_in_L1 = 1;
	chip->blink_led = 1;
	chip->msi_en = msi_en;
	chip->hp_watch_bios_hotplug = 0;
	chip->max_payload = 0;
	chip->phy_voltage = 0;

	chip->support_ms_8bit = 1;
	chip->s3_pwr_off_delay = 1000;
}