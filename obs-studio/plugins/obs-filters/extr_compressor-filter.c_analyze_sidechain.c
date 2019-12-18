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
typedef  int uint32_t ;
struct compressor_data {int const envelope_buf_len; float attack_gain; float release_gain; float** sidechain_buf; float* envelope_buf; size_t num_channels; float envelope; } ;

/* Variables and functions */
 float fabsf (float) ; 
 float fmaxf (float,float) ; 
 int /*<<< orphan*/  get_sidechain_data (struct compressor_data*,int const) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  resize_env_buffer (struct compressor_data*,int const) ; 

__attribute__((used)) static void analyze_sidechain(struct compressor_data *cd,
			      const uint32_t num_samples)
{
	if (cd->envelope_buf_len < num_samples) {
		resize_env_buffer(cd, num_samples);
	}

	get_sidechain_data(cd, num_samples);

	const float attack_gain = cd->attack_gain;
	const float release_gain = cd->release_gain;
	float **sidechain_buf = cd->sidechain_buf;

	memset(cd->envelope_buf, 0, num_samples * sizeof(cd->envelope_buf[0]));
	for (size_t chan = 0; chan < cd->num_channels; ++chan) {
		if (!sidechain_buf[chan])
			continue;

		float *envelope_buf = cd->envelope_buf;
		float env = cd->envelope;
		for (uint32_t i = 0; i < num_samples; ++i) {
			const float env_in = fabsf(sidechain_buf[chan][i]);

			if (env < env_in) {
				env = env_in + attack_gain * (env - env_in);
			} else {
				env = env_in + release_gain * (env - env_in);
			}
			envelope_buf[i] = fmaxf(envelope_buf[i], env);
		}
	}
	cd->envelope = cd->envelope_buf[num_samples - 1];
}