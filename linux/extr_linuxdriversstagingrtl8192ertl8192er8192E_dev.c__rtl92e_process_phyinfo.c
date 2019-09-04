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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtllib_rx_stats {unsigned int Seq_Num; size_t SignalStrength; int* RxMIMOSignalStrength; size_t RxPWDBAll; scalar_t__ SignalQuality; int* RxMIMOSignalQuality; scalar_t__ bToSelfBA; scalar_t__ bPacketBeacon; scalar_t__ bPacketToSelf; scalar_t__ bIsCCK; int /*<<< orphan*/  bPacketMatchBSSID; int /*<<< orphan*/  rssi; int /*<<< orphan*/  bIsAMPDU; } ;
struct rtllib_hdr_3addr {int /*<<< orphan*/  seq_ctl; } ;
struct TYPE_4__ {size_t* slide_signal_strength; size_t slide_rssi_total; int* rx_rssi_percentage; size_t* Slide_Beacon_pwdb; size_t Slide_Beacon_Total; size_t* slide_evm; size_t slide_evm_total; size_t signal_quality; size_t last_signal_strength_inpercent; int* rx_evm_percentage; int /*<<< orphan*/  num_process_phyinfo; int /*<<< orphan*/  signal_strength; } ;
struct r8192_priv {int undecorated_smoothed_pwdb; TYPE_2__ stats; TYPE_1__* rtllib; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DBG ; 
 int /*<<< orphan*/  COMP_RXDESC ; 
 size_t PHY_Beacon_RSSI_SLID_WIN_MAX ; 
 size_t PHY_RSSI_SLID_WIN_MAX ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_C ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int RX_SMOOTH ; 
 unsigned int WLAN_GET_SEQ_FRAG (int /*<<< orphan*/ ) ; 
 unsigned int WLAN_GET_SEQ_SEQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_is_legal_rf_path (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rtl92e_translate_to_dbm (struct r8192_priv*,size_t) ; 
 int /*<<< orphan*/  rtl92e_update_rx_statistics (struct r8192_priv*,struct rtllib_rx_stats*) ; 

__attribute__((used)) static void _rtl92e_process_phyinfo(struct r8192_priv *priv, u8 *buffer,
				    struct rtllib_rx_stats *prev_st,
				    struct rtllib_rx_stats *curr_st)
{
	bool bcheck = false;
	u8	rfpath;
	u32 ij, tmp_val;
	static u32 slide_rssi_index, slide_rssi_statistics;
	static u32 slide_evm_index, slide_evm_statistics;
	static u32 last_rssi, last_evm;
	static u32 slide_beacon_adc_pwdb_index;
	static u32 slide_beacon_adc_pwdb_statistics;
	static u32 last_beacon_adc_pwdb;
	struct rtllib_hdr_3addr *hdr;
	u16 sc;
	unsigned int frag, seq;

	hdr = (struct rtllib_hdr_3addr *)buffer;
	sc = le16_to_cpu(hdr->seq_ctl);
	frag = WLAN_GET_SEQ_FRAG(sc);
	seq = WLAN_GET_SEQ_SEQ(sc);
	curr_st->Seq_Num = seq;
	if (!prev_st->bIsAMPDU)
		bcheck = true;

	if (slide_rssi_statistics++ >= PHY_RSSI_SLID_WIN_MAX) {
		slide_rssi_statistics = PHY_RSSI_SLID_WIN_MAX;
		last_rssi = priv->stats.slide_signal_strength[slide_rssi_index];
		priv->stats.slide_rssi_total -= last_rssi;
	}
	priv->stats.slide_rssi_total += prev_st->SignalStrength;

	priv->stats.slide_signal_strength[slide_rssi_index++] =
					 prev_st->SignalStrength;
	if (slide_rssi_index >= PHY_RSSI_SLID_WIN_MAX)
		slide_rssi_index = 0;

	tmp_val = priv->stats.slide_rssi_total/slide_rssi_statistics;
	priv->stats.signal_strength = rtl92e_translate_to_dbm(priv,
							      (u8)tmp_val);
	curr_st->rssi = priv->stats.signal_strength;
	if (!prev_st->bPacketMatchBSSID) {
		if (!prev_st->bToSelfBA)
			return;
	}

	if (!bcheck)
		return;

	priv->stats.num_process_phyinfo++;
	if (!prev_st->bIsCCK && prev_st->bPacketToSelf) {
		for (rfpath = RF90_PATH_A; rfpath < RF90_PATH_C; rfpath++) {
			if (!rtl92e_is_legal_rf_path(priv->rtllib->dev, rfpath))
				continue;
			RT_TRACE(COMP_DBG,
				 "Jacken -> pPreviousstats->RxMIMOSignalStrength[rfpath]  = %d\n",
				 prev_st->RxMIMOSignalStrength[rfpath]);
			if (priv->stats.rx_rssi_percentage[rfpath] == 0) {
				priv->stats.rx_rssi_percentage[rfpath] =
					 prev_st->RxMIMOSignalStrength[rfpath];
			}
			if (prev_st->RxMIMOSignalStrength[rfpath]  >
			    priv->stats.rx_rssi_percentage[rfpath]) {
				priv->stats.rx_rssi_percentage[rfpath] =
					((priv->stats.rx_rssi_percentage[rfpath]
					* (RX_SMOOTH - 1)) +
					(prev_st->RxMIMOSignalStrength
					[rfpath])) / (RX_SMOOTH);
				priv->stats.rx_rssi_percentage[rfpath] =
					 priv->stats.rx_rssi_percentage[rfpath]
					 + 1;
			} else {
				priv->stats.rx_rssi_percentage[rfpath] =
				   ((priv->stats.rx_rssi_percentage[rfpath] *
				   (RX_SMOOTH-1)) +
				   (prev_st->RxMIMOSignalStrength[rfpath])) /
				   (RX_SMOOTH);
			}
			RT_TRACE(COMP_DBG,
				 "Jacken -> priv->RxStats.RxRSSIPercentage[rfPath]  = %d\n",
				 priv->stats.rx_rssi_percentage[rfpath]);
		}
	}


	if (prev_st->bPacketBeacon) {
		if (slide_beacon_adc_pwdb_statistics++ >=
		    PHY_Beacon_RSSI_SLID_WIN_MAX) {
			slide_beacon_adc_pwdb_statistics =
					 PHY_Beacon_RSSI_SLID_WIN_MAX;
			last_beacon_adc_pwdb = priv->stats.Slide_Beacon_pwdb
					       [slide_beacon_adc_pwdb_index];
			priv->stats.Slide_Beacon_Total -= last_beacon_adc_pwdb;
		}
		priv->stats.Slide_Beacon_Total += prev_st->RxPWDBAll;
		priv->stats.Slide_Beacon_pwdb[slide_beacon_adc_pwdb_index] =
							 prev_st->RxPWDBAll;
		slide_beacon_adc_pwdb_index++;
		if (slide_beacon_adc_pwdb_index >= PHY_Beacon_RSSI_SLID_WIN_MAX)
			slide_beacon_adc_pwdb_index = 0;
		prev_st->RxPWDBAll = priv->stats.Slide_Beacon_Total /
				     slide_beacon_adc_pwdb_statistics;
		if (prev_st->RxPWDBAll >= 3)
			prev_st->RxPWDBAll -= 3;
	}

	RT_TRACE(COMP_RXDESC, "Smooth %s PWDB = %d\n",
				prev_st->bIsCCK ? "CCK" : "OFDM",
				prev_st->RxPWDBAll);

	if (prev_st->bPacketToSelf || prev_st->bPacketBeacon ||
	    prev_st->bToSelfBA) {
		if (priv->undecorated_smoothed_pwdb < 0)
			priv->undecorated_smoothed_pwdb = prev_st->RxPWDBAll;
		if (prev_st->RxPWDBAll > (u32)priv->undecorated_smoothed_pwdb) {
			priv->undecorated_smoothed_pwdb =
					(((priv->undecorated_smoothed_pwdb) *
					(RX_SMOOTH-1)) +
					(prev_st->RxPWDBAll)) / (RX_SMOOTH);
			priv->undecorated_smoothed_pwdb =
					 priv->undecorated_smoothed_pwdb + 1;
		} else {
			priv->undecorated_smoothed_pwdb =
					(((priv->undecorated_smoothed_pwdb) *
					(RX_SMOOTH-1)) +
					(prev_st->RxPWDBAll)) / (RX_SMOOTH);
		}
		rtl92e_update_rx_statistics(priv, prev_st);
	}

	if (prev_st->SignalQuality != 0) {
		if (prev_st->bPacketToSelf || prev_st->bPacketBeacon ||
		    prev_st->bToSelfBA) {
			if (slide_evm_statistics++ >= PHY_RSSI_SLID_WIN_MAX) {
				slide_evm_statistics = PHY_RSSI_SLID_WIN_MAX;
				last_evm =
					 priv->stats.slide_evm[slide_evm_index];
				priv->stats.slide_evm_total -= last_evm;
			}

			priv->stats.slide_evm_total += prev_st->SignalQuality;

			priv->stats.slide_evm[slide_evm_index++] =
						 prev_st->SignalQuality;
			if (slide_evm_index >= PHY_RSSI_SLID_WIN_MAX)
				slide_evm_index = 0;

			tmp_val = priv->stats.slide_evm_total /
				  slide_evm_statistics;
			priv->stats.signal_quality = tmp_val;
			priv->stats.last_signal_strength_inpercent = tmp_val;
		}

		if (prev_st->bPacketToSelf ||
		    prev_st->bPacketBeacon ||
		    prev_st->bToSelfBA) {
			for (ij = 0; ij < 2; ij++) {
				if (prev_st->RxMIMOSignalQuality[ij] != -1) {
					if (priv->stats.rx_evm_percentage[ij] == 0)
						priv->stats.rx_evm_percentage[ij] =
						   prev_st->RxMIMOSignalQuality[ij];
					priv->stats.rx_evm_percentage[ij] =
					  ((priv->stats.rx_evm_percentage[ij] *
					  (RX_SMOOTH - 1)) +
					  (prev_st->RxMIMOSignalQuality[ij])) /
					  (RX_SMOOTH);
				}
			}
		}
	}
}