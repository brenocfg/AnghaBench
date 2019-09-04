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
 unsigned int OXYGEN_RATE_176400 ; 
 unsigned int OXYGEN_RATE_192000 ; 
 unsigned int OXYGEN_RATE_32000 ; 
 unsigned int OXYGEN_RATE_44100 ; 
 unsigned int OXYGEN_RATE_48000 ; 
 unsigned int OXYGEN_RATE_64000 ; 
 unsigned int OXYGEN_RATE_88200 ; 
 unsigned int OXYGEN_RATE_96000 ; 
 int params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static unsigned int oxygen_rate(struct snd_pcm_hw_params *hw_params)
{
	switch (params_rate(hw_params)) {
	case 32000:
		return OXYGEN_RATE_32000;
	case 44100:
		return OXYGEN_RATE_44100;
	default: /* 48000 */
		return OXYGEN_RATE_48000;
	case 64000:
		return OXYGEN_RATE_64000;
	case 88200:
		return OXYGEN_RATE_88200;
	case 96000:
		return OXYGEN_RATE_96000;
	case 176400:
		return OXYGEN_RATE_176400;
	case 192000:
		return OXYGEN_RATE_192000;
	}
}