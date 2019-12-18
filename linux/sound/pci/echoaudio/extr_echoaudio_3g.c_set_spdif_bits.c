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
struct echoaudio {scalar_t__ non_audio_spdif; scalar_t__ professional_spdif; } ;

/* Variables and functions */
 int E3G_SPDIF_24_BIT ; 
 int E3G_SPDIF_COPY_PERMIT ; 
 int E3G_SPDIF_FORMAT_CLEAR_MASK ; 
 int E3G_SPDIF_NOT_AUDIO ; 
 int E3G_SPDIF_PRO_MODE ; 
 int E3G_SPDIF_SAMPLE_RATE0 ; 
 int E3G_SPDIF_SAMPLE_RATE1 ; 
 int E3G_SPDIF_TWO_CHANNEL ; 

__attribute__((used)) static u32 set_spdif_bits(struct echoaudio *chip, u32 control_reg, u32 rate)
{
	control_reg &= E3G_SPDIF_FORMAT_CLEAR_MASK;

	switch (rate) {
	case 32000 :
		control_reg |= E3G_SPDIF_SAMPLE_RATE0 | E3G_SPDIF_SAMPLE_RATE1;
		break;
	case 44100 :
		if (chip->professional_spdif)
			control_reg |= E3G_SPDIF_SAMPLE_RATE0;
		break;
	case 48000 :
		control_reg |= E3G_SPDIF_SAMPLE_RATE1;
		break;
	}

	if (chip->professional_spdif)
		control_reg |= E3G_SPDIF_PRO_MODE;

	if (chip->non_audio_spdif)
		control_reg |= E3G_SPDIF_NOT_AUDIO;

	control_reg |= E3G_SPDIF_24_BIT | E3G_SPDIF_TWO_CHANNEL |
		E3G_SPDIF_COPY_PERMIT;

	return control_reg;
}