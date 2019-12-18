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
typedef  scalar_t__ u32 ;

/* Variables and functions */
#define  AUD_SAMPLE_RATE_176_4 134 
 scalar_t__ AUD_SAMPLE_RATE_176_4_DP_1_62_MAUD_VAL ; 
 scalar_t__ AUD_SAMPLE_RATE_176_4_DP_2_7_MAUD_VAL ; 
#define  AUD_SAMPLE_RATE_32 133 
 scalar_t__ AUD_SAMPLE_RATE_32_DP_1_62_MAUD_VAL ; 
 scalar_t__ AUD_SAMPLE_RATE_32_DP_2_7_MAUD_VAL ; 
#define  AUD_SAMPLE_RATE_44_1 132 
 scalar_t__ AUD_SAMPLE_RATE_44_1_DP_1_62_MAUD_VAL ; 
 scalar_t__ AUD_SAMPLE_RATE_44_1_DP_2_7_MAUD_VAL ; 
#define  AUD_SAMPLE_RATE_48 131 
 scalar_t__ AUD_SAMPLE_RATE_48_DP_1_62_MAUD_VAL ; 
 scalar_t__ AUD_SAMPLE_RATE_48_DP_2_7_MAUD_VAL ; 
#define  AUD_SAMPLE_RATE_88_2 130 
 scalar_t__ AUD_SAMPLE_RATE_88_2_DP_1_62_MAUD_VAL ; 
 scalar_t__ AUD_SAMPLE_RATE_88_2_DP_2_7_MAUD_VAL ; 
#define  AUD_SAMPLE_RATE_96 129 
 scalar_t__ AUD_SAMPLE_RATE_96_DP_1_62_MAUD_VAL ; 
 scalar_t__ AUD_SAMPLE_RATE_96_DP_2_7_MAUD_VAL ; 
 scalar_t__ DP_1_62_GHZ ; 
 scalar_t__ DP_2_7_GHZ ; 
 scalar_t__ EINVAL ; 
#define  HAD_MAX_RATE 128 
 scalar_t__ HAD_MAX_RATE_DP_1_62_MAUD_VAL ; 
 scalar_t__ HAD_MAX_RATE_DP_2_7_MAUD_VAL ; 

__attribute__((used)) static int had_calculate_maud_value(u32 aud_samp_freq, u32 link_rate)
{
	u32 maud_val;

	/* Select maud according to DP 1.2 spec */
	if (link_rate == DP_2_7_GHZ) {
		switch (aud_samp_freq) {
		case AUD_SAMPLE_RATE_32:
			maud_val = AUD_SAMPLE_RATE_32_DP_2_7_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_44_1:
			maud_val = AUD_SAMPLE_RATE_44_1_DP_2_7_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_48:
			maud_val = AUD_SAMPLE_RATE_48_DP_2_7_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_88_2:
			maud_val = AUD_SAMPLE_RATE_88_2_DP_2_7_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_96:
			maud_val = AUD_SAMPLE_RATE_96_DP_2_7_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_176_4:
			maud_val = AUD_SAMPLE_RATE_176_4_DP_2_7_MAUD_VAL;
			break;

		case HAD_MAX_RATE:
			maud_val = HAD_MAX_RATE_DP_2_7_MAUD_VAL;
			break;

		default:
			maud_val = -EINVAL;
			break;
		}
	} else if (link_rate == DP_1_62_GHZ) {
		switch (aud_samp_freq) {
		case AUD_SAMPLE_RATE_32:
			maud_val = AUD_SAMPLE_RATE_32_DP_1_62_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_44_1:
			maud_val = AUD_SAMPLE_RATE_44_1_DP_1_62_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_48:
			maud_val = AUD_SAMPLE_RATE_48_DP_1_62_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_88_2:
			maud_val = AUD_SAMPLE_RATE_88_2_DP_1_62_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_96:
			maud_val = AUD_SAMPLE_RATE_96_DP_1_62_MAUD_VAL;
			break;

		case AUD_SAMPLE_RATE_176_4:
			maud_val = AUD_SAMPLE_RATE_176_4_DP_1_62_MAUD_VAL;
			break;

		case HAD_MAX_RATE:
			maud_val = HAD_MAX_RATE_DP_1_62_MAUD_VAL;
			break;

		default:
			maud_val = -EINVAL;
			break;
		}
	} else
		maud_val = -EINVAL;

	return maud_val;
}