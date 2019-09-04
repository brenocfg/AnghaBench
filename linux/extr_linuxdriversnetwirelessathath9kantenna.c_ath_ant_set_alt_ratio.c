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
struct ath_hw_antcomb_conf {scalar_t__ main_lna_conf; scalar_t__ alt_lna_conf; } ;
struct ath_ant_comb {scalar_t__ rssi_second; scalar_t__ rssi_third; scalar_t__ first_quick_scan_conf; scalar_t__ second_quick_scan_conf; scalar_t__ main_conf; scalar_t__ second_ratio; scalar_t__ first_ratio; } ;

/* Variables and functions */
 scalar_t__ ATH_ANT_DIV_COMB_LNA1 ; 
 scalar_t__ ATH_ANT_DIV_COMB_LNA2 ; 

__attribute__((used)) static void ath_ant_set_alt_ratio(struct ath_ant_comb *antcomb,
				  struct ath_hw_antcomb_conf *conf)
{
	/* set alt to the conf with maximun ratio */
	if (antcomb->first_ratio && antcomb->second_ratio) {
		if (antcomb->rssi_second > antcomb->rssi_third) {
			/* first alt*/
			if ((antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
			    (antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2))
				/* Set alt LNA1 or LNA2*/
				if (conf->main_lna_conf == ATH_ANT_DIV_COMB_LNA2)
					conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				else
					conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
			else
				/* Set alt to A+B or A-B */
				conf->alt_lna_conf =
					antcomb->first_quick_scan_conf;
		} else if ((antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
			   (antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2)) {
			/* Set alt LNA1 or LNA2 */
			if (conf->main_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			else
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		} else {
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->second_quick_scan_conf;
		}
	} else if (antcomb->first_ratio) {
		/* first alt */
		if ((antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
		    (antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2))
			/* Set alt LNA1 or LNA2 */
			if (conf->main_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			else
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		else
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->first_quick_scan_conf;
	} else if (antcomb->second_ratio) {
		/* second alt */
		if ((antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
		    (antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2))
			/* Set alt LNA1 or LNA2 */
			if (conf->main_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			else
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		else
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->second_quick_scan_conf;
	} else {
		/* main is largest */
		if ((antcomb->main_conf == ATH_ANT_DIV_COMB_LNA1) ||
		    (antcomb->main_conf == ATH_ANT_DIV_COMB_LNA2))
			/* Set alt LNA1 or LNA2 */
			if (conf->main_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			else
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		else
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->main_conf;
	}
}