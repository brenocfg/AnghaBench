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
struct rx_fwinfo {scalar_t__ RxRate; scalar_t__ BW; scalar_t__ RxHT; } ;
struct rx_desc {int dummy; } ;
struct rtllib_rx_stats {int bPacketMatchBSSID; int bPacketToSelf; int bIsCCK; int bPacketBeacon; int bToSelfBA; int* RxMIMOSignalQuality; int RxPWDBAll; int RecvSignalPower; int SignalQuality; int* RxMIMOSignalStrength; int RxPower; int SignalStrength; } ;
struct TYPE_4__ {long* rxSNRdB; int /*<<< orphan*/ * received_bwtype; int /*<<< orphan*/  numqry_phystatusHT; int /*<<< orphan*/  numqry_phystatusCCK; int /*<<< orphan*/  numqry_phystatus; } ;
struct r8192_priv {TYPE_2__ stats; scalar_t__* brfpath_rxenable; TYPE_1__* rtllib; } ;
struct phy_sts_ofdm_819xpci {int* trsw_gain_X; int* rxsnr_X; int pwdb_all; int* rxevm_X; int rxsc_sgien_exflg; } ;
struct phy_sts_cck_819xpci {int cck_agc_rpt; int sq_rpt; } ;
struct phy_ofdm_rx_status_rxsc_sgien_exintfflag {int rxsc; } ;
typedef  int s8 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DESC90_RATEMCS15 ; 
 scalar_t__ DESC90_RATEMCS8 ; 
 int RF90_PATH_A ; 
 int RF90_PATH_MAX ; 
 scalar_t__ _rtl92e_signal_scale_mapping (struct r8192_priv*,long) ; 
 int /*<<< orphan*/  memset (struct rtllib_rx_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rFPGA0_XA_HSSIParameter2 ; 
 int rtl92e_evm_db_to_percent (int) ; 
 int rtl92e_get_bb_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rtl92e_rx_db_to_percent (int) ; 
 int rx_hal_is_cck_rate (struct rx_fwinfo*) ; 

__attribute__((used)) static void _rtl92e_query_rxphystatus(
	struct r8192_priv *priv,
	struct rtllib_rx_stats *pstats,
	struct rx_desc  *pdesc,
	struct rx_fwinfo   *pdrvinfo,
	struct rtllib_rx_stats *precord_stats,
	bool bpacket_match_bssid,
	bool bpacket_toself,
	bool bPacketBeacon,
	bool bToSelfBA
	)
{
	struct phy_sts_ofdm_819xpci *pofdm_buf;
	struct phy_sts_cck_819xpci *pcck_buf;
	struct phy_ofdm_rx_status_rxsc_sgien_exintfflag *prxsc;
	u8 *prxpkt;
	u8 i, max_spatial_stream, tmp_rxsnr, tmp_rxevm, rxsc_sgien_exflg;
	s8 rx_pwr[4], rx_pwr_all = 0;
	s8 rx_snrX, rx_evmX;
	u8 evm, pwdb_all;
	u32 RSSI, total_rssi = 0;
	u8 is_cck_rate = 0;
	u8 rf_rx_num = 0;
	static	u8 check_reg824;
	static	u32 reg824_bit9;

	priv->stats.numqry_phystatus++;

	is_cck_rate = rx_hal_is_cck_rate(pdrvinfo);
	memset(precord_stats, 0, sizeof(struct rtllib_rx_stats));
	pstats->bPacketMatchBSSID = precord_stats->bPacketMatchBSSID =
				    bpacket_match_bssid;
	pstats->bPacketToSelf = precord_stats->bPacketToSelf = bpacket_toself;
	pstats->bIsCCK = precord_stats->bIsCCK = is_cck_rate;
	pstats->bPacketBeacon = precord_stats->bPacketBeacon = bPacketBeacon;
	pstats->bToSelfBA = precord_stats->bToSelfBA = bToSelfBA;
	if (check_reg824 == 0) {
		reg824_bit9 = rtl92e_get_bb_reg(priv->rtllib->dev,
						rFPGA0_XA_HSSIParameter2,
						0x200);
		check_reg824 = 1;
	}


	prxpkt = (u8 *)pdrvinfo;

	prxpkt += sizeof(struct rx_fwinfo);

	pcck_buf = (struct phy_sts_cck_819xpci *)prxpkt;
	pofdm_buf = (struct phy_sts_ofdm_819xpci *)prxpkt;

	pstats->RxMIMOSignalQuality[0] = -1;
	pstats->RxMIMOSignalQuality[1] = -1;
	precord_stats->RxMIMOSignalQuality[0] = -1;
	precord_stats->RxMIMOSignalQuality[1] = -1;

	if (is_cck_rate) {
		u8 report;

		priv->stats.numqry_phystatusCCK++;
		if (!reg824_bit9) {
			report = pcck_buf->cck_agc_rpt & 0xc0;
			report >>= 6;
			switch (report) {
			case 0x3:
				rx_pwr_all = -35 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				break;
			case 0x2:
				rx_pwr_all = -23 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				break;
			case 0x1:
				rx_pwr_all = -11 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				break;
			case 0x0:
				rx_pwr_all = 8 - (pcck_buf->cck_agc_rpt & 0x3e);
				break;
			}
		} else {
			report = pcck_buf->cck_agc_rpt & 0x60;
			report >>= 5;
			switch (report) {
			case 0x3:
				rx_pwr_all = -35 -
					((pcck_buf->cck_agc_rpt &
					0x1f) << 1);
				break;
			case 0x2:
				rx_pwr_all = -23 -
					((pcck_buf->cck_agc_rpt &
					 0x1f) << 1);
				break;
			case 0x1:
				rx_pwr_all = -11 -
					 ((pcck_buf->cck_agc_rpt &
					 0x1f) << 1);
				break;
			case 0x0:
				rx_pwr_all = -8 -
					 ((pcck_buf->cck_agc_rpt &
					 0x1f) << 1);
				break;
			}
		}

		pwdb_all = rtl92e_rx_db_to_percent(rx_pwr_all);
		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		pstats->RecvSignalPower = rx_pwr_all;

		if (bpacket_match_bssid) {
			u8	sq;

			if (pstats->RxPWDBAll > 40) {
				sq = 100;
			} else {
				sq = pcck_buf->sq_rpt;

				if (pcck_buf->sq_rpt > 64)
					sq = 0;
				else if (pcck_buf->sq_rpt < 20)
					sq = 100;
				else
					sq = ((64-sq) * 100) / 44;
			}
			pstats->SignalQuality = sq;
			precord_stats->SignalQuality = sq;
			pstats->RxMIMOSignalQuality[0] = sq;
			precord_stats->RxMIMOSignalQuality[0] = sq;
			pstats->RxMIMOSignalQuality[1] = -1;
			precord_stats->RxMIMOSignalQuality[1] = -1;
		}
	} else {
		priv->stats.numqry_phystatusHT++;
		for (i = RF90_PATH_A; i < RF90_PATH_MAX; i++) {
			if (priv->brfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] = ((pofdm_buf->trsw_gain_X[i] & 0x3F) *
				     2) - 110;

			tmp_rxsnr = pofdm_buf->rxsnr_X[i];
			rx_snrX = (s8)(tmp_rxsnr);
			rx_snrX /= 2;
			priv->stats.rxSNRdB[i] = (long)rx_snrX;

			RSSI = rtl92e_rx_db_to_percent(rx_pwr[i]);
			if (priv->brfpath_rxenable[i])
				total_rssi += RSSI;

			if (bpacket_match_bssid) {
				pstats->RxMIMOSignalStrength[i] = (u8) RSSI;
				precord_stats->RxMIMOSignalStrength[i] =
								(u8) RSSI;
			}
		}


		rx_pwr_all = (((pofdm_buf->pwdb_all) >> 1) & 0x7f) - 106;
		pwdb_all = rtl92e_rx_db_to_percent(rx_pwr_all);

		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		pstats->RxPower = precord_stats->RxPower =	rx_pwr_all;
		pstats->RecvSignalPower = rx_pwr_all;
		if (pdrvinfo->RxHT && pdrvinfo->RxRate >= DESC90_RATEMCS8 &&
		    pdrvinfo->RxRate <= DESC90_RATEMCS15)
			max_spatial_stream = 2;
		else
			max_spatial_stream = 1;

		for (i = 0; i < max_spatial_stream; i++) {
			tmp_rxevm = pofdm_buf->rxevm_X[i];
			rx_evmX = (s8)(tmp_rxevm);

			rx_evmX /= 2;

			evm = rtl92e_evm_db_to_percent(rx_evmX);
			if (bpacket_match_bssid) {
				if (i == 0) {
					pstats->SignalQuality = evm & 0xff;
					precord_stats->SignalQuality = evm & 0xff;
				}
				pstats->RxMIMOSignalQuality[i] = evm & 0xff;
				precord_stats->RxMIMOSignalQuality[i] = evm & 0xff;
			}
		}


		rxsc_sgien_exflg = pofdm_buf->rxsc_sgien_exflg;
		prxsc = (struct phy_ofdm_rx_status_rxsc_sgien_exintfflag *)
			&rxsc_sgien_exflg;
		if (pdrvinfo->BW)
			priv->stats.received_bwtype[1+prxsc->rxsc]++;
		else
			priv->stats.received_bwtype[0]++;
	}

	if (is_cck_rate) {
		pstats->SignalStrength = precord_stats->SignalStrength =
					 (u8)(_rtl92e_signal_scale_mapping(priv,
					 (long)pwdb_all));

	} else {
		if (rf_rx_num != 0)
			pstats->SignalStrength = precord_stats->SignalStrength =
					 (u8)(_rtl92e_signal_scale_mapping(priv,
					 (long)(total_rssi /= rf_rx_num)));
	}
}