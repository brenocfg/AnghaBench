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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct wmi_phyerr_ev_arg {scalar_t__ rssi_combined; } ;
struct phyerr_fft_report {int /*<<< orphan*/  reg1; int /*<<< orphan*/  reg0; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_REGULATORY ; 
 int /*<<< orphan*/  ATH10K_DFS_STAT_INC (struct ath10k*,int /*<<< orphan*/ ) ; 
 int DFS_PEAK_MAG_THOLD_POSSIBLY_FALSE ; 
 scalar_t__ DFS_RSSI_POSSIBLY_FALSE ; 
 int EINVAL ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG0_BASE_PWR_DB ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG0_FFT_CHN_IDX ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG0_PEAK_SIDX ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG0_TOTAL_GAIN_DB ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG1_AVGPWR_DB ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG1_NUM_STR_BINS_IB ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG1_PEAK_MAG ; 
 int /*<<< orphan*/  SEARCH_FFT_REPORT_REG1_RELPWR_DB ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pulses_discarded ; 

__attribute__((used)) static int ath10k_dfs_fft_report(struct ath10k *ar,
				 struct wmi_phyerr_ev_arg *phyerr,
				 const struct phyerr_fft_report *fftr,
				 u64 tsf)
{
	u32 reg0, reg1;
	u8 rssi, peak_mag;

	reg0 = __le32_to_cpu(fftr->reg0);
	reg1 = __le32_to_cpu(fftr->reg1);
	rssi = phyerr->rssi_combined;

	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi phyerr fft report total_gain_db %d base_pwr_db %d fft_chn_idx %d peak_sidx %d\n",
		   MS(reg0, SEARCH_FFT_REPORT_REG0_TOTAL_GAIN_DB),
		   MS(reg0, SEARCH_FFT_REPORT_REG0_BASE_PWR_DB),
		   MS(reg0, SEARCH_FFT_REPORT_REG0_FFT_CHN_IDX),
		   MS(reg0, SEARCH_FFT_REPORT_REG0_PEAK_SIDX));
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi phyerr fft report rel_pwr_db %d avgpwr_db %d peak_mag %d num_store_bin %d\n",
		   MS(reg1, SEARCH_FFT_REPORT_REG1_RELPWR_DB),
		   MS(reg1, SEARCH_FFT_REPORT_REG1_AVGPWR_DB),
		   MS(reg1, SEARCH_FFT_REPORT_REG1_PEAK_MAG),
		   MS(reg1, SEARCH_FFT_REPORT_REG1_NUM_STR_BINS_IB));

	peak_mag = MS(reg1, SEARCH_FFT_REPORT_REG1_PEAK_MAG);

	/* false event detection */
	if (rssi == DFS_RSSI_POSSIBLY_FALSE &&
	    peak_mag < 2 * DFS_PEAK_MAG_THOLD_POSSIBLY_FALSE) {
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY, "dfs false pulse detected\n");
		ATH10K_DFS_STAT_INC(ar, pulses_discarded);
		return -EINVAL;
	}

	return 0;
}