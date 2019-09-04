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
typedef  enum ath10k_ampdu_subfrm_num { ____Placeholder_ath10k_ampdu_subfrm_num } ath10k_ampdu_subfrm_num ;

/* Variables and functions */
#define  ATH10K_AMPDU_SUBFRM_NUM_10 135 
#define  ATH10K_AMPDU_SUBFRM_NUM_20 134 
#define  ATH10K_AMPDU_SUBFRM_NUM_30 133 
#define  ATH10K_AMPDU_SUBFRM_NUM_40 132 
#define  ATH10K_AMPDU_SUBFRM_NUM_50 131 
#define  ATH10K_AMPDU_SUBFRM_NUM_60 130 
#define  ATH10K_AMPDU_SUBFRM_NUM_MAX 129 
#define  ATH10K_AMPDU_SUBFRM_NUM_MORE 128 

__attribute__((used)) static char *get_num_ampdu_subfrm_str(enum ath10k_ampdu_subfrm_num i)
{
	switch (i) {
	case ATH10K_AMPDU_SUBFRM_NUM_10:
		return "upto 10";
	case ATH10K_AMPDU_SUBFRM_NUM_20:
		return "11-20";
	case ATH10K_AMPDU_SUBFRM_NUM_30:
		return "21-30";
	case ATH10K_AMPDU_SUBFRM_NUM_40:
		return "31-40";
	case ATH10K_AMPDU_SUBFRM_NUM_50:
		return "41-50";
	case ATH10K_AMPDU_SUBFRM_NUM_60:
		return "51-60";
	case ATH10K_AMPDU_SUBFRM_NUM_MORE:
		return ">60";
	case ATH10K_AMPDU_SUBFRM_NUM_MAX:
		return "0";
	}

	return "0";
}