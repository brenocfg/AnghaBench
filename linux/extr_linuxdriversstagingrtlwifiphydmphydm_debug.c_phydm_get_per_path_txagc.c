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
typedef  int u32 ;
struct phy_dm_struct {int support_ic_type; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 scalar_t__ ODM_RATE1M ; 
 scalar_t__ ODM_RATE6M ; 
 scalar_t__ ODM_RATEMCS0 ; 
 scalar_t__ ODM_RATEMCS16 ; 
 scalar_t__ ODM_RATEMCS24 ; 
 scalar_t__ ODM_RATEMCS8 ; 
 scalar_t__ ODM_RATEVHTSS1MCS0 ; 
 scalar_t__ ODM_RATEVHTSS2MCS0 ; 
 scalar_t__ ODM_RATEVHTSS3MCS0 ; 
 scalar_t__ ODM_RATEVHTSS4MCS0 ; 
 scalar_t__ ODM_RF_PATH_A ; 
 scalar_t__ ODM_RF_PATH_B ; 
 int ODM_RTL8197F ; 
 int ODM_RTL8821C ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*) ; 
 scalar_t__ config_phydm_read_txagc_check (scalar_t__) ; 
 scalar_t__ phydm_api_get_txagc (struct phy_dm_struct*,int,scalar_t__) ; 

__attribute__((used)) static void phydm_get_per_path_txagc(void *dm_void, u8 path, u32 *_used,
				     char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 rate_idx;
	u8 txagc;
	u32 used = *_used;
	u32 out_len = *_out_len;

	if (((dm->support_ic_type & (ODM_RTL8822B | ODM_RTL8197F)) &&
	     path <= ODM_RF_PATH_B) ||
	    ((dm->support_ic_type & (ODM_RTL8821C)) &&
	     path <= ODM_RF_PATH_A)) {
		for (rate_idx = 0; rate_idx <= 0x53; rate_idx++) {
			if (rate_idx == ODM_RATE1M)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "  %-35s\n", "CCK====>");
			else if (rate_idx == ODM_RATE6M)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "OFDM====>");
			else if (rate_idx == ODM_RATEMCS0)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "HT 1ss====>");
			else if (rate_idx == ODM_RATEMCS8)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "HT 2ss====>");
			else if (rate_idx == ODM_RATEMCS16)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "HT 3ss====>");
			else if (rate_idx == ODM_RATEMCS24)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "HT 4ss====>");
			else if (rate_idx == ODM_RATEVHTSS1MCS0)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "VHT 1ss====>");
			else if (rate_idx == ODM_RATEVHTSS2MCS0)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "VHT 2ss====>");
			else if (rate_idx == ODM_RATEVHTSS3MCS0)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "VHT 3ss====>");
			else if (rate_idx == ODM_RATEVHTSS4MCS0)
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "\n  %-35s\n", "VHT 4ss====>");

			txagc = phydm_api_get_txagc(
				dm, (enum odm_rf_radio_path)path, rate_idx);
			if (config_phydm_read_txagc_check(txagc))
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "  0x%02x    ", txagc);
			else
				PHYDM_SNPRINTF(output + used, out_len - used,
					       "  0x%s    ", "xx");
		}
	}
}