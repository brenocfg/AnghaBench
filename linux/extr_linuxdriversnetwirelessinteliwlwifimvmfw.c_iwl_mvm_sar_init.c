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
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IWL_DEBUG_RADIO (struct iwl_mvm*,char*,int) ; 
 int iwl_mvm_sar_get_ewrd_table (struct iwl_mvm*) ; 
 int iwl_mvm_sar_get_wrds_table (struct iwl_mvm*) ; 
 int iwl_mvm_sar_select_profile (struct iwl_mvm*,int,int) ; 

__attribute__((used)) static int iwl_mvm_sar_init(struct iwl_mvm *mvm)
{
	int ret;

	ret = iwl_mvm_sar_get_wrds_table(mvm);
	if (ret < 0) {
		IWL_DEBUG_RADIO(mvm,
				"WRDS SAR BIOS table invalid or unavailable. (%d)\n",
				ret);
		/*
		 * If not available, don't fail and don't bother with EWRD.
		 * Return 1 to tell that we can't use WGDS either.
		 */
		return 1;
	}

	ret = iwl_mvm_sar_get_ewrd_table(mvm);
	/* if EWRD is not available, we can still use WRDS, so don't fail */
	if (ret < 0)
		IWL_DEBUG_RADIO(mvm,
				"EWRD SAR BIOS table invalid or unavailable. (%d)\n",
				ret);

	/* choose profile 1 (WRDS) as default for both chains */
	ret = iwl_mvm_sar_select_profile(mvm, 1, 1);

	/*
	 * If we don't have profile 0 from BIOS, just skip it.  This
	 * means that SAR Geo will not be enabled either, even if we
	 * have other valid profiles.
	 */
	if (ret == -ENOENT)
		return 1;

	return ret;
}