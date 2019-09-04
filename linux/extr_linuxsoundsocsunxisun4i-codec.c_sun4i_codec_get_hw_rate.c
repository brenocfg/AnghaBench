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
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int sun4i_codec_get_hw_rate(struct snd_pcm_hw_params *params)
{
	unsigned int rate = params_rate(params);

	switch (rate) {
	case 192000:
	case 176400:
		return 6;

	case 96000:
	case 88200:
		return 7;

	case 48000:
	case 44100:
		return 0;

	case 32000:
	case 33075:
		return 1;

	case 24000:
	case 22050:
		return 2;

	case 16000:
	case 14700:
		return 3;

	case 12000:
	case 11025:
		return 4;

	case 8000:
	case 7350:
		return 5;

	default:
		return -EINVAL;
	}
}