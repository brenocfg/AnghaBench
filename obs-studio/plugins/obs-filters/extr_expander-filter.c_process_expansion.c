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
typedef  scalar_t__ uint32_t ;
struct expander_data {float attack_gain; float release_gain; scalar_t__ gaindB_len; float** gaindB; size_t num_channels; float threshold; float slope; float* gaindB_buf; float output_gain; int /*<<< orphan*/ ** envelope_buf; } ;

/* Variables and functions */
 int MAX_AUDIO_CHANNELS ; 
 float db_to_mul (int /*<<< orphan*/ ) ; 
 float fmaxf (float,float) ; 
 int /*<<< orphan*/  fminf (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,scalar_t__) ; 
 float mul_to_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize_gaindB_buffer (struct expander_data*,scalar_t__) ; 

__attribute__((used)) static inline void process_expansion(struct expander_data *cd, float **samples,
				     uint32_t num_samples)
{
	const float attack_gain = cd->attack_gain;
	const float release_gain = cd->release_gain;

	if (cd->gaindB_len < num_samples)
		resize_gaindB_buffer(cd, num_samples);
	for (int i = 0; i < MAX_AUDIO_CHANNELS; i++)
		memset(cd->gaindB[i], 0,
		       num_samples * sizeof(cd->gaindB[i][0]));

	for (size_t chan = 0; chan < cd->num_channels; chan++) {
		for (size_t i = 0; i < num_samples; ++i) {
			// gain stage of expansion
			float env_db = mul_to_db(cd->envelope_buf[chan][i]);
			float gain =
				cd->threshold - env_db > 0.0f
					? fmaxf(cd->slope * (cd->threshold -
							     env_db),
						-60.0f)
					: 0.0f;
			// ballistics (attack/release)
			if (i > 0) {
				if (gain > cd->gaindB[chan][i - 1])
					cd->gaindB[chan][i] =
						attack_gain *
							cd->gaindB[chan][i - 1] +
						(1.0f - attack_gain) * gain;
				else
					cd->gaindB[chan][i] =
						release_gain *
							cd->gaindB[chan][i - 1] +
						(1.0f - release_gain) * gain;
			} else {
				if (gain > cd->gaindB_buf[chan])
					cd->gaindB[chan][i] =
						attack_gain *
							cd->gaindB_buf[chan] +
						(1.0f - attack_gain) * gain;
				else
					cd->gaindB[chan][i] =
						release_gain *
							cd->gaindB_buf[chan] +
						(1.0f - release_gain) * gain;
			}

			gain = db_to_mul(fminf(0, cd->gaindB[chan][i]));
			if (samples[chan])
				samples[chan][i] *= gain * cd->output_gain;
		}
		cd->gaindB_buf[chan] = cd->gaindB[chan][num_samples - 1];
	}
}