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
typedef  int u8 ;
typedef  int u32 ;
struct rx_fwinfo_8723e {int* cfosho; int* gain_trsw; int* rxsnr; int pwdb_all; int /*<<< orphan*/ * rxevm; } ;
struct rtl_stats {int is_cck; int packet_matchbssid; int packet_toself; int packet_beacon; int* rx_mimo_signalquality; int rx_pwdb_all; int signalquality; int* rx_mimo_signalstrength; scalar_t__ rate; int signalstrength; scalar_t__ is_ht; void* recvsignalpower; void* rxpower; } ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; } ;
struct TYPE_4__ {long* rx_snr_db; } ;
struct TYPE_3__ {int* rfpath_rxenable; } ;
struct rtl_priv {TYPE_2__ stats; TYPE_1__ dm; } ;
struct phy_sts_cck_8723e_t {int cck_agc_rpt; int sq_rpt; } ;
struct ieee80211_hw {int dummy; } ;
typedef  void* s8 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ DESC92C_RATEMCS15 ; 
 scalar_t__ DESC92C_RATEMCS8 ; 
 scalar_t__ ERFON ; 
 int RF6052_MAX_PATH ; 
 int RF90_PATH_A ; 
 int /*<<< orphan*/  RFPGA0_XA_HSSIPARAMETER2 ; 
 int rtl_evm_db_to_percentage (int /*<<< orphan*/ ) ; 
 scalar_t__ rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_query_rxpwrpercentage (void*) ; 
 scalar_t__ rtl_signal_scale_mapping (struct ieee80211_hw*,int) ; 

__attribute__((used)) static void _rtl8723e_query_rxphystatus(struct ieee80211_hw *hw,
					struct rtl_stats *pstatus, u8 *pdesc,
					struct rx_fwinfo_8723e *p_drvinfo,
					bool bpacket_match_bssid,
					bool bpacket_toself, bool packet_beacon)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	struct phy_sts_cck_8723e_t *cck_buf;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool is_cck = pstatus->is_cck;

	/* Record it for next packet processing */
	pstatus->packet_matchbssid = bpacket_match_bssid;
	pstatus->packet_toself = bpacket_toself;
	pstatus->packet_beacon = packet_beacon;
	pstatus->rx_mimo_signalquality[0] = -1;
	pstatus->rx_mimo_signalquality[1] = -1;

	if (is_cck) {
		u8 report, cck_highpwr;

		/* CCK Driver info Structure is not the same as OFDM packet. */
		cck_buf = (struct phy_sts_cck_8723e_t *)p_drvinfo;

		/* (1)Hardware does not provide RSSI for CCK */
		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (for rate adaptive)
		 */
		if (ppsc->rfpwr_state == ERFON)
			cck_highpwr = (u8)rtl_get_bbreg(hw,
					RFPGA0_XA_HSSIPARAMETER2,
					BIT(9));
		else
			cck_highpwr = false;

		if (!cck_highpwr) {
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;
			report = cck_buf->cck_agc_rpt & 0xc0;
			report = report >> 6;
			switch (report) {
			case 0x3:
				rx_pwr_all = -46 - (cck_agc_rpt & 0x3e);
				break;
			case 0x2:
				rx_pwr_all = -26 - (cck_agc_rpt & 0x3e);
				break;
			case 0x1:
				rx_pwr_all = -12 - (cck_agc_rpt & 0x3e);
				break;
			case 0x0:
				rx_pwr_all = 16 - (cck_agc_rpt & 0x3e);
				break;
			}
		} else {
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;
			report = p_drvinfo->cfosho[0] & 0x60;
			report = report >> 5;
			switch (report) {
			case 0x3:
				rx_pwr_all = -46 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			case 0x2:
				rx_pwr_all = -26 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			case 0x1:
				rx_pwr_all = -12 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			case 0x0:
				rx_pwr_all = 16 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			}
		}

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		/* CCK gain is smaller than OFDM/MCS gain,  */
		/* so we add gain diff by experiences,
		 * the val is 6
		 */
		pwdb_all += 6;
		if (pwdb_all > 100)
			pwdb_all = 100;
		/* modify the offset to make the same
		 * gain index with OFDM.
		 */
		if (pwdb_all > 34 && pwdb_all <= 42)
			pwdb_all -= 2;
		else if (pwdb_all > 26 && pwdb_all <= 34)
			pwdb_all -= 6;
		else if (pwdb_all > 14 && pwdb_all <= 26)
			pwdb_all -= 8;
		else if (pwdb_all > 4 && pwdb_all <= 14)
			pwdb_all -= 4;

		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->recvsignalpower = rx_pwr_all;

		/* (3) Get Signal Quality (EVM) */
		if (bpacket_match_bssid) {
			u8 sq;

			if (pstatus->rx_pwdb_all > 40)
				sq = 100;
			else {
				sq = cck_buf->sq_rpt;
				if (sq > 64)
					sq = 0;
				else if (sq < 20)
					sq = 100;
				else
					sq = ((64 - sq) * 100) / 44;
			}

			pstatus->signalquality = sq;
			pstatus->rx_mimo_signalquality[0] = sq;
			pstatus->rx_mimo_signalquality[1] = -1;
		}
	} else {
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;

		/* (1)Get RSSI for HT rate */
		for (i = RF90_PATH_A; i < RF6052_MAX_PATH; i++) {

			/* we will judge RF RX path now. */
			if (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] = ((p_drvinfo->gain_trsw[i] &
				      0x3f) * 2) - 110;

			/* Translate DBM to percentage. */
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;

			/* Get Rx snr value in DB */
			rtlpriv->stats.rx_snr_db[i] =
				(long)(p_drvinfo->rxsnr[i] / 2);

			/* Record Signal Strength for next packet */
			if (bpacket_match_bssid)
				pstatus->rx_mimo_signalstrength[i] = (u8)rssi;
		}

		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (for rate adaptive)
		 */
		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 110;

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->rxpower = rx_pwr_all;
		pstatus->recvsignalpower = rx_pwr_all;

		/* (3)EVM of HT rate */
		if (pstatus->is_ht && pstatus->rate >= DESC92C_RATEMCS8 &&
		    pstatus->rate <= DESC92C_RATEMCS15)
			max_spatial_stream = 2;
		else
			max_spatial_stream = 1;

		for (i = 0; i < max_spatial_stream; i++) {
			evm = rtl_evm_db_to_percentage(p_drvinfo->rxevm[i]);

			if (bpacket_match_bssid) {
				/* Fill value in RFD, Get the first
				 * spatial stream only
				 */
				if (i == 0)
					pstatus->signalquality =
						(u8)(evm & 0xff);
				pstatus->rx_mimo_signalquality[i] =
					(u8)(evm & 0xff);
			}
		}
	}

	/* UI BSS List signal strength(in percentage),
	 * make it good looking, from 0~100.
	 */
	if (is_cck)
		pstatus->signalstrength = (u8)(rtl_signal_scale_mapping(hw,
			pwdb_all));
	else if (rf_rx_num != 0)
		pstatus->signalstrength = (u8)(rtl_signal_scale_mapping(hw,
			total_rssi /= rf_rx_num));
}