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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int /*<<< orphan*/  fw_subversion; int /*<<< orphan*/  fw_version; } ;
struct phy_dm_struct {int support_ic_type; scalar_t__ cut_version; scalar_t__ adapter; scalar_t__ is_mp_chip; } ;

/* Variables and functions */
 int ACS_VERSION ; 
 int ADAPTIVITY_VERSION ; 
 int ANTDIV_VERSION ; 
 int CFO_TRACKING_VERSION ; 
 char* COMMIT_BY_8822B ; 
 int DIG_VERSION ; 
 int DYNAMIC_BBPWRSAV_VERSION ; 
 int DYNAMIC_LA_MODE ; 
 int DYNAMIC_RX_PATH_VERSION ; 
 int DYNAMIC_TXPWR_VERSION ; 
 int EDCATURBO_VERSION ; 
 scalar_t__ ODM_CUT_A ; 
 scalar_t__ ODM_CUT_B ; 
 scalar_t__ ODM_CUT_C ; 
 scalar_t__ ODM_CUT_D ; 
 scalar_t__ ODM_CUT_E ; 
 scalar_t__ ODM_CUT_F ; 
 scalar_t__ ODM_CUT_I ; 
 int ODM_RTL8188E ; 
 int ODM_RTL8822B ; 
 int PHYDM_CODE_BASE ; 
 int PHYDM_RELEASE_DATE ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*,...) ; 
 int PHY_CONFIG_VERSION_8822B ; 
 int POWRTRACKING_VERSION ; 
 int RAINFO_VERSION ; 
 int RELEASE_DATE_8822B ; 
 int RELEASE_VERSION_8822B ; 
 int odm_get_hw_img_version (struct phy_dm_struct*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 

void phydm_basic_profile(void *dm_void, u32 *_used, char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	char *cut = NULL;
	char *ic_type = NULL;
	u32 used = *_used;
	u32 out_len = *_out_len;
	u32 date = 0;
	char *commit_by = NULL;
	u32 release_ver = 0;

	PHYDM_SNPRINTF(output + used, out_len - used, "%-35s\n",
		       "% Basic Profile %");

	if (dm->support_ic_type == ODM_RTL8188E) {
	} else if (dm->support_ic_type == ODM_RTL8822B) {
		ic_type = "RTL8822B";
		date = RELEASE_DATE_8822B;
		commit_by = COMMIT_BY_8822B;
		release_ver = RELEASE_VERSION_8822B;
	}

	/* JJ ADD 20161014 */

	PHYDM_SNPRINTF(output + used, out_len - used,
		       "  %-35s: %s (MP Chip: %s)\n", "IC type", ic_type,
		       dm->is_mp_chip ? "Yes" : "No");

	if (dm->cut_version == ODM_CUT_A)
		cut = "A";
	else if (dm->cut_version == ODM_CUT_B)
		cut = "B";
	else if (dm->cut_version == ODM_CUT_C)
		cut = "C";
	else if (dm->cut_version == ODM_CUT_D)
		cut = "D";
	else if (dm->cut_version == ODM_CUT_E)
		cut = "E";
	else if (dm->cut_version == ODM_CUT_F)
		cut = "F";
	else if (dm->cut_version == ODM_CUT_I)
		cut = "I";
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "cut version", cut);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %d\n",
		       "PHY Parameter version", odm_get_hw_img_version(dm));
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %d\n",
		       "PHY Parameter Commit date", date);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "PHY Parameter Commit by", commit_by);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %d\n",
		       "PHY Parameter Release version", release_ver);

	{
		struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;
		struct rtl_hal *rtlhal = rtl_hal(rtlpriv);

		PHYDM_SNPRINTF(output + used, out_len - used,
			       "  %-35s: %d (Subversion: %d)\n", "FW version",
			       rtlhal->fw_version, rtlhal->fw_subversion);
	}
	/* 1 PHY DM version List */
	PHYDM_SNPRINTF(output + used, out_len - used, "%-35s\n",
		       "% PHYDM version %");
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Code base", PHYDM_CODE_BASE);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Release Date", PHYDM_RELEASE_DATE);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "adaptivity", ADAPTIVITY_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n", "DIG",
		       DIG_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Dynamic BB PowerSaving", DYNAMIC_BBPWRSAV_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "CFO Tracking", CFO_TRACKING_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Antenna Diversity", ANTDIV_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Power Tracking", POWRTRACKING_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Dynamic TxPower", DYNAMIC_TXPWR_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "RA Info", RAINFO_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Auto channel Selection", ACS_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "EDCA Turbo", EDCATURBO_VERSION);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "LA mode", DYNAMIC_LA_MODE);
	PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
		       "Dynamic RX path", DYNAMIC_RX_PATH_VERSION);

	if (dm->support_ic_type & ODM_RTL8822B)
		PHYDM_SNPRINTF(output + used, out_len - used, "  %-35s: %s\n",
			       "PHY config 8822B", PHY_CONFIG_VERSION_8822B);

	*_used = used;
	*_out_len = out_len;
}