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
typedef  size_t uint32_t ;
struct TYPE_2__ {scalar_t__ data; } ;
struct obs_source {TYPE_1__ audio_data; } ;
typedef  enum obs_balance_type { ____Placeholder_obs_balance_type } obs_balance_type ;

/* Variables and functions */
 float M_PI ; 
#define  OBS_BALANCE_TYPE_LINEAR 130 
#define  OBS_BALANCE_TYPE_SINE_LAW 129 
#define  OBS_BALANCE_TYPE_SQUARE_LAW 128 
 float sinf (float) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void process_audio_balancing(struct obs_source *source, uint32_t frames,
				    float balance, enum obs_balance_type type)
{
	float **data = (float **)source->audio_data.data;

	switch (type) {
	case OBS_BALANCE_TYPE_SINE_LAW:
		for (uint32_t frame = 0; frame < frames; frame++) {
			data[0][frame] = data[0][frame] *
					 sinf((1.0f - balance) * (M_PI / 2.0f));
			data[1][frame] =
				data[1][frame] * sinf(balance * (M_PI / 2.0f));
		}
		break;
	case OBS_BALANCE_TYPE_SQUARE_LAW:
		for (uint32_t frame = 0; frame < frames; frame++) {
			data[0][frame] = data[0][frame] * sqrtf(1.0f - balance);
			data[1][frame] = data[1][frame] * sqrtf(balance);
		}
		break;
	case OBS_BALANCE_TYPE_LINEAR:
		for (uint32_t frame = 0; frame < frames; frame++) {
			data[0][frame] = data[0][frame] * (1.0f - balance);
			data[1][frame] = data[1][frame] * balance;
		}
		break;
	default:
		break;
	}
}