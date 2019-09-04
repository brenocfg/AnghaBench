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
struct ath_hw_antcomb_conf {int main_lna_conf; int alt_lna_conf; int lna1_lna2_switch_delta; } ;
struct ath_ant_comb {int rssi_lna2; int rssi_lna1; int scan; int rssi_add; int rssi_sub; } ;

/* Variables and functions */
#define  ATH_ANT_DIV_COMB_LNA1 131 
#define  ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2 130 
#define  ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2 129 
#define  ATH_ANT_DIV_COMB_LNA2 128 

__attribute__((used)) static void ath_ant_try_scan(struct ath_ant_comb *antcomb,
			     struct ath_hw_antcomb_conf *conf,
			     int curr_alt_set, int alt_rssi_avg,
			     int main_rssi_avg)
{
	switch (curr_alt_set) {
	case ATH_ANT_DIV_COMB_LNA2:
		antcomb->rssi_lna2 = alt_rssi_avg;
		antcomb->rssi_lna1 = main_rssi_avg;
		antcomb->scan = true;
		/* set to A+B */
		conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA1;
		conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		break;
	case ATH_ANT_DIV_COMB_LNA1:
		antcomb->rssi_lna1 = alt_rssi_avg;
		antcomb->rssi_lna2 = main_rssi_avg;
		antcomb->scan = true;
		/* set to A+B */
		conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		break;
	case ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2:
		antcomb->rssi_add = alt_rssi_avg;
		antcomb->scan = true;
		/* set to A-B */
		conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		break;
	case ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2:
		antcomb->rssi_sub = alt_rssi_avg;
		antcomb->scan = false;
		if (antcomb->rssi_lna2 >
		    (antcomb->rssi_lna1 + conf->lna1_lna2_switch_delta)) {
			/* use LNA2 as main LNA */
			if ((antcomb->rssi_add > antcomb->rssi_lna1) &&
			    (antcomb->rssi_add > antcomb->rssi_sub)) {
				/* set to A+B */
				conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA2;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
			} else if (antcomb->rssi_sub >
				   antcomb->rssi_lna1) {
				/* set to A-B */
				conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA2;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
			} else {
				/* set to LNA1 */
				conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA2;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			}
		} else {
			/* use LNA1 as main LNA */
			if ((antcomb->rssi_add > antcomb->rssi_lna2) &&
			    (antcomb->rssi_add > antcomb->rssi_sub)) {
				/* set to A+B */
				conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
			} else if (antcomb->rssi_sub >
				   antcomb->rssi_lna1) {
				/* set to A-B */
				conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
			} else {
				/* set to LNA2 */
				conf->main_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
			}
		}
		break;
	default:
		break;
	}
}