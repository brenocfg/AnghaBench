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
typedef  scalar_t__ u32 ;
struct survey_info {int filled; void* time_busy; void* time; } ;
struct TYPE_2__ {int cc_wraparound_type; } ;
struct ath10k {TYPE_1__ hw_params; } ;
typedef  enum ath10k_hw_cc_wraparound_type { ____Placeholder_ath10k_hw_cc_wraparound_type } ath10k_hw_cc_wraparound_type ;

/* Variables and functions */
#define  ATH10K_HW_CC_WRAP_DISABLED 130 
#define  ATH10K_HW_CC_WRAP_SHIFTED_ALL 129 
#define  ATH10K_HW_CC_WRAP_SHIFTED_EACH 128 
 void* CCNT_TO_MSEC (struct ath10k*,scalar_t__) ; 
 int SURVEY_INFO_TIME ; 
 int SURVEY_INFO_TIME_BUSY ; 

void ath10k_hw_fill_survey_time(struct ath10k *ar, struct survey_info *survey,
				u32 cc, u32 rcc, u32 cc_prev, u32 rcc_prev)
{
	u32 cc_fix = 0;
	u32 rcc_fix = 0;
	enum ath10k_hw_cc_wraparound_type wraparound_type;

	survey->filled |= SURVEY_INFO_TIME |
			  SURVEY_INFO_TIME_BUSY;

	wraparound_type = ar->hw_params.cc_wraparound_type;

	if (cc < cc_prev || rcc < rcc_prev) {
		switch (wraparound_type) {
		case ATH10K_HW_CC_WRAP_SHIFTED_ALL:
			if (cc < cc_prev) {
				cc_fix = 0x7fffffff;
				survey->filled &= ~SURVEY_INFO_TIME_BUSY;
			}
			break;
		case ATH10K_HW_CC_WRAP_SHIFTED_EACH:
			if (cc < cc_prev)
				cc_fix = 0x7fffffff;

			if (rcc < rcc_prev)
				rcc_fix = 0x7fffffff;
			break;
		case ATH10K_HW_CC_WRAP_DISABLED:
			break;
		}
	}

	cc -= cc_prev - cc_fix;
	rcc -= rcc_prev - rcc_fix;

	survey->time = CCNT_TO_MSEC(ar, cc);
	survey->time_busy = CCNT_TO_MSEC(ar, rcc);
}