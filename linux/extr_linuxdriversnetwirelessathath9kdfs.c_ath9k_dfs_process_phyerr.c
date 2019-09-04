#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u16 ;
struct pulse_event {int freq; scalar_t__ width; int chirp; scalar_t__ ts; int /*<<< orphan*/  rssi; } ;
struct ath_softc {scalar_t__ dfs_prev_pulse_ts; struct ath_hw* sc_ah; } ;
struct ath_rx_status {scalar_t__ rs_phyerr; int rs_datalen; int* rs_rssi_ctl; int* rs_rssi_ext; } ;
struct ath_radar_data {int rssi; int ext_rssi; char pulse_bw_info; char pulse_length_ext; char pulse_length_pri; } ;
struct ath_hw {TYPE_1__* curchan; } ;
struct ath_common {int dummy; } ;
struct TYPE_3__ {int channel; } ;

/* Variables and functions */
 scalar_t__ ATH9K_PHYERR_FALSE_RADAR_EXT ; 
 scalar_t__ ATH9K_PHYERR_RADAR ; 
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  DFS_STAT_INC (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int EXT_CH_RADAR_FOUND ; 
 scalar_t__ IS_CHAN_HT40 (TYPE_1__*) ; 
 scalar_t__ IS_CHAN_HT40PLUS (TYPE_1__*) ; 
 scalar_t__ MAX_CHIRP_PULSE_WIDTH ; 
 scalar_t__ MIN_CHIRP_PULSE_WIDTH ; 
 int PRI_CH_RADAR_FOUND ; 
 int ath9k_check_chirping (struct ath_softc*,void*,int,int,int) ; 
 int /*<<< orphan*/  ath9k_dfs_process_radar_pulse (struct ath_softc*,struct pulse_event*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_postprocess_radar_event (struct ath_softc*,struct ath_radar_data*,struct pulse_event*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  datalen_discards ; 
 int /*<<< orphan*/  pulses_no_dfs ; 
 int /*<<< orphan*/  pulses_total ; 

void ath9k_dfs_process_phyerr(struct ath_softc *sc, void *data,
			      struct ath_rx_status *rs, u64 mactime)
{
	struct ath_radar_data ard;
	u16 datalen;
	char *vdata_end;
	struct pulse_event pe;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);

	DFS_STAT_INC(sc, pulses_total);
	if ((rs->rs_phyerr != ATH9K_PHYERR_RADAR) &&
	    (rs->rs_phyerr != ATH9K_PHYERR_FALSE_RADAR_EXT)) {
		ath_dbg(common, DFS,
			"Error: rs_phyer=0x%x not a radar error\n",
			rs->rs_phyerr);
		DFS_STAT_INC(sc, pulses_no_dfs);
		return;
	}

	datalen = rs->rs_datalen;
	if (datalen == 0) {
		DFS_STAT_INC(sc, datalen_discards);
		return;
	}

	ard.rssi = rs->rs_rssi_ctl[0];
	ard.ext_rssi = rs->rs_rssi_ext[0];

	/*
	 * hardware stores this as 8 bit signed value.
	 * we will cap it at 0 if it is a negative number
	 */
	if (ard.rssi & 0x80)
		ard.rssi = 0;
	if (ard.ext_rssi & 0x80)
		ard.ext_rssi = 0;

	vdata_end = data + datalen;
	ard.pulse_bw_info = vdata_end[-1];
	ard.pulse_length_ext = vdata_end[-2];
	ard.pulse_length_pri = vdata_end[-3];
	pe.freq = ah->curchan->channel;
	pe.ts = mactime;
	if (!ath9k_postprocess_radar_event(sc, &ard, &pe))
		return;

	if (pe.width > MIN_CHIRP_PULSE_WIDTH &&
	    pe.width < MAX_CHIRP_PULSE_WIDTH) {
		bool is_ctl = !!(ard.pulse_bw_info & PRI_CH_RADAR_FOUND);
		bool is_ext = !!(ard.pulse_bw_info & EXT_CH_RADAR_FOUND);
		int clen = datalen - 3;
		pe.chirp = ath9k_check_chirping(sc, data, clen, is_ctl, is_ext);
	} else {
		pe.chirp = false;
	}

	ath_dbg(common, DFS,
		"ath9k_dfs_process_phyerr: type=%d, freq=%d, ts=%llu, "
		"width=%d, rssi=%d, delta_ts=%llu\n",
		ard.pulse_bw_info, pe.freq, pe.ts, pe.width, pe.rssi,
		pe.ts - sc->dfs_prev_pulse_ts);
	sc->dfs_prev_pulse_ts = pe.ts;
	if (ard.pulse_bw_info & PRI_CH_RADAR_FOUND)
		ath9k_dfs_process_radar_pulse(sc, &pe);
	if (IS_CHAN_HT40(ah->curchan) &&
	    ard.pulse_bw_info & EXT_CH_RADAR_FOUND) {
		pe.freq += IS_CHAN_HT40PLUS(ah->curchan) ? 20 : -20;
		ath9k_dfs_process_radar_pulse(sc, &pe);
	}
}