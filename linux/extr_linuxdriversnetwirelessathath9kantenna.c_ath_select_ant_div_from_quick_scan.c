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
struct ath_hw_antcomb_conf {int main_lna_conf; int lna1_lna2_switch_delta; int /*<<< orphan*/  alt_lna_conf; } ;
struct ath_ant_comb {int quick_scan_cnt; int main_conf; int rssi_first; int rssi_second; int first_ratio; int alt_good; int scan_not_start; int scan; int rssi_third; int rssi_lna1; int rssi_lna2; int second_ratio; int /*<<< orphan*/  total_pkt_count; int /*<<< orphan*/  second_quick_scan_conf; int /*<<< orphan*/  first_quick_scan_conf; } ;

/* Variables and functions */
#define  ATH_ANT_DIV_COMB_LNA1 130 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_LNA1_DELTA_HI ; 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_LNA1_DELTA_LOW ; 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_LNA1_DELTA_MID ; 
#define  ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2 129 
#define  ATH_ANT_DIV_COMB_LNA2 128 
 int /*<<< orphan*/  ath_ant_set_alt_ratio (struct ath_ant_comb*,struct ath_hw_antcomb_conf*) ; 
 int /*<<< orphan*/  ath_is_alt_ant_ratio_better (struct ath_ant_comb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath_select_ant_div_from_quick_scan(struct ath_ant_comb *antcomb,
				       struct ath_hw_antcomb_conf *div_ant_conf,
				       int main_rssi_avg, int alt_rssi_avg,
				       int alt_ratio)
{
	/* alt_good */
	switch (antcomb->quick_scan_cnt) {
	case 0:
		/* set alt to main, and alt to first conf */
		div_ant_conf->main_lna_conf = antcomb->main_conf;
		div_ant_conf->alt_lna_conf = antcomb->first_quick_scan_conf;
		break;
	case 1:
		/* set alt to main, and alt to first conf */
		div_ant_conf->main_lna_conf = antcomb->main_conf;
		div_ant_conf->alt_lna_conf = antcomb->second_quick_scan_conf;
		antcomb->rssi_first = main_rssi_avg;
		antcomb->rssi_second = alt_rssi_avg;

		if (antcomb->main_conf == ATH_ANT_DIV_COMB_LNA1) {
			/* main is LNA1 */
			if (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = true;
			else
				antcomb->first_ratio = false;
		} else if (antcomb->main_conf == ATH_ANT_DIV_COMB_LNA2) {
			if (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_MID,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = true;
			else
				antcomb->first_ratio = false;
		} else {
			if (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						0,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = true;
			else
				antcomb->first_ratio = false;
		}
		break;
	case 2:
		antcomb->alt_good = false;
		antcomb->scan_not_start = false;
		antcomb->scan = false;
		antcomb->rssi_first = main_rssi_avg;
		antcomb->rssi_third = alt_rssi_avg;

		switch(antcomb->second_quick_scan_conf) {
		case ATH_ANT_DIV_COMB_LNA1:
			antcomb->rssi_lna1 = alt_rssi_avg;
			break;
		case ATH_ANT_DIV_COMB_LNA2:
			antcomb->rssi_lna2 = alt_rssi_avg;
			break;
		case ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2:
			if (antcomb->main_conf == ATH_ANT_DIV_COMB_LNA2)
				antcomb->rssi_lna2 = main_rssi_avg;
			else if (antcomb->main_conf == ATH_ANT_DIV_COMB_LNA1)
				antcomb->rssi_lna1 = main_rssi_avg;
			break;
		default:
			break;
		}

		if (antcomb->rssi_lna2 > antcomb->rssi_lna1 +
		    div_ant_conf->lna1_lna2_switch_delta)
			div_ant_conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		else
			div_ant_conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA1;

		if (antcomb->main_conf == ATH_ANT_DIV_COMB_LNA1) {
			if (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = true;
			else
				antcomb->second_ratio = false;
		} else if (antcomb->main_conf == ATH_ANT_DIV_COMB_LNA2) {
			if (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_MID,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = true;
			else
				antcomb->second_ratio = false;
		} else {
			if (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						0,
						main_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = true;
			else
				antcomb->second_ratio = false;
		}

		ath_ant_set_alt_ratio(antcomb, div_ant_conf);

		break;
	default:
		break;
	}
}