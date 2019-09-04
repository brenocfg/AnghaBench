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
typedef  enum ath10k_cal_mode { ____Placeholder_ath10k_cal_mode } ath10k_cal_mode ;

/* Variables and functions */
#define  ATH10K_CAL_MODE_DT 133 
#define  ATH10K_CAL_MODE_EEPROM 132 
#define  ATH10K_CAL_MODE_FILE 131 
#define  ATH10K_CAL_MODE_OTP 130 
#define  ATH10K_PRE_CAL_MODE_DT 129 
#define  ATH10K_PRE_CAL_MODE_FILE 128 

__attribute__((used)) static inline const char *ath10k_cal_mode_str(enum ath10k_cal_mode mode)
{
	switch (mode) {
	case ATH10K_CAL_MODE_FILE:
		return "file";
	case ATH10K_CAL_MODE_OTP:
		return "otp";
	case ATH10K_CAL_MODE_DT:
		return "dt";
	case ATH10K_PRE_CAL_MODE_FILE:
		return "pre-cal-file";
	case ATH10K_PRE_CAL_MODE_DT:
		return "pre-cal-dt";
	case ATH10K_CAL_MODE_EEPROM:
		return "eeprom";
	}

	return "unknown";
}