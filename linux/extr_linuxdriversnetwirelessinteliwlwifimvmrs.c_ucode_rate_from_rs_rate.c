#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rs_rate {int index; int ant; int type; int bw; scalar_t__ ldpc; scalar_t__ sgi; scalar_t__ stbc; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int plcp; int plcp_ht_siso; int plcp_ht_mimo2; int plcp_vht_siso; int plcp_vht_mimo2; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int IWL_FIRST_CCK_RATE ; 
 int IWL_FIRST_HT_RATE ; 
 int IWL_FIRST_VHT_RATE ; 
 int IWL_LAST_CCK_RATE ; 
 int IWL_LAST_HT_RATE ; 
 int IWL_LAST_VHT_RATE ; 
 int RATE_MCS_ANT_ABC_MSK ; 
 int RATE_MCS_ANT_AB_MSK ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_LDPC_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 int RATE_MCS_STBC_MSK ; 
 int RATE_MCS_VHT_MSK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ is_ht (struct rs_rate*) ; 
 scalar_t__ is_ht_mimo2 (struct rs_rate*) ; 
 scalar_t__ is_ht_siso (struct rs_rate*) ; 
 scalar_t__ is_legacy (struct rs_rate*) ; 
 scalar_t__ is_siso (struct rs_rate*) ; 
 scalar_t__ is_vht (struct rs_rate*) ; 
 scalar_t__ is_vht_mimo2 (struct rs_rate*) ; 
 scalar_t__ is_vht_siso (struct rs_rate*) ; 
 TYPE_1__* iwl_rates ; 

__attribute__((used)) static u32 ucode_rate_from_rs_rate(struct iwl_mvm *mvm,
				  struct rs_rate *rate)
{
	u32 ucode_rate = 0;
	int index = rate->index;

	ucode_rate |= ((rate->ant << RATE_MCS_ANT_POS) &
			 RATE_MCS_ANT_ABC_MSK);

	if (is_legacy(rate)) {
		ucode_rate |= iwl_rates[index].plcp;
		if (index >= IWL_FIRST_CCK_RATE && index <= IWL_LAST_CCK_RATE)
			ucode_rate |= RATE_MCS_CCK_MSK;
		return ucode_rate;
	}

	if (is_ht(rate)) {
		if (index < IWL_FIRST_HT_RATE || index > IWL_LAST_HT_RATE) {
			IWL_ERR(mvm, "Invalid HT rate index %d\n", index);
			index = IWL_LAST_HT_RATE;
		}
		ucode_rate |= RATE_MCS_HT_MSK;

		if (is_ht_siso(rate))
			ucode_rate |= iwl_rates[index].plcp_ht_siso;
		else if (is_ht_mimo2(rate))
			ucode_rate |= iwl_rates[index].plcp_ht_mimo2;
		else
			WARN_ON_ONCE(1);
	} else if (is_vht(rate)) {
		if (index < IWL_FIRST_VHT_RATE || index > IWL_LAST_VHT_RATE) {
			IWL_ERR(mvm, "Invalid VHT rate index %d\n", index);
			index = IWL_LAST_VHT_RATE;
		}
		ucode_rate |= RATE_MCS_VHT_MSK;
		if (is_vht_siso(rate))
			ucode_rate |= iwl_rates[index].plcp_vht_siso;
		else if (is_vht_mimo2(rate))
			ucode_rate |= iwl_rates[index].plcp_vht_mimo2;
		else
			WARN_ON_ONCE(1);

	} else {
		IWL_ERR(mvm, "Invalid rate->type %d\n", rate->type);
	}

	if (is_siso(rate) && rate->stbc) {
		/* To enable STBC we need to set both a flag and ANT_AB */
		ucode_rate |= RATE_MCS_ANT_AB_MSK;
		ucode_rate |= RATE_MCS_STBC_MSK;
	}

	ucode_rate |= rate->bw;
	if (rate->sgi)
		ucode_rate |= RATE_MCS_SGI_MSK;
	if (rate->ldpc)
		ucode_rate |= RATE_MCS_LDPC_MSK;

	return ucode_rate;
}