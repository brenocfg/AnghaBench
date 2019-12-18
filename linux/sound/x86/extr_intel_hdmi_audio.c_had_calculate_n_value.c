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

/* Variables and functions */
#define  AUD_SAMPLE_RATE_176_4 134 
#define  AUD_SAMPLE_RATE_32 133 
#define  AUD_SAMPLE_RATE_44_1 132 
#define  AUD_SAMPLE_RATE_48 131 
#define  AUD_SAMPLE_RATE_88_2 130 
#define  AUD_SAMPLE_RATE_96 129 
 int EINVAL ; 
#define  HAD_MAX_RATE 128 

__attribute__((used)) static int had_calculate_n_value(u32 aud_samp_freq)
{
	int n_val;

	/* Select N according to HDMI 1.3a spec*/
	switch (aud_samp_freq) {
	case AUD_SAMPLE_RATE_32:
		n_val = 4096;
		break;

	case AUD_SAMPLE_RATE_44_1:
		n_val = 6272;
		break;

	case AUD_SAMPLE_RATE_48:
		n_val = 6144;
		break;

	case AUD_SAMPLE_RATE_88_2:
		n_val = 12544;
		break;

	case AUD_SAMPLE_RATE_96:
		n_val = 12288;
		break;

	case AUD_SAMPLE_RATE_176_4:
		n_val = 25088;
		break;

	case HAD_MAX_RATE:
		n_val = 24576;
		break;

	default:
		n_val = -EINVAL;
		break;
	}
	return n_val;
}