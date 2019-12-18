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

/* Variables and functions */
 int /*<<< orphan*/  async_delay_filter ; 
 int /*<<< orphan*/  chroma_key_filter ; 
 int /*<<< orphan*/  color_filter ; 
 int /*<<< orphan*/  color_grade_filter ; 
 int /*<<< orphan*/  color_key_filter ; 
 int /*<<< orphan*/  compressor_filter ; 
 int /*<<< orphan*/  crop_filter ; 
 int /*<<< orphan*/  expander_filter ; 
 int /*<<< orphan*/  gain_filter ; 
 int /*<<< orphan*/  gpu_delay_filter ; 
 int /*<<< orphan*/  invert_polarity_filter ; 
 int /*<<< orphan*/  limiter_filter ; 
 int /*<<< orphan*/  luma_key_filter ; 
 int /*<<< orphan*/  mask_filter ; 
 int /*<<< orphan*/  noise_gate_filter ; 
 int /*<<< orphan*/  noise_suppress_filter ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scale_filter ; 
 int /*<<< orphan*/  scroll_filter ; 
 int /*<<< orphan*/  sharpness_filter ; 

bool obs_module_load(void)
{
	obs_register_source(&mask_filter);
	obs_register_source(&crop_filter);
	obs_register_source(&gain_filter);
	obs_register_source(&color_filter);
	obs_register_source(&scale_filter);
	obs_register_source(&scroll_filter);
	obs_register_source(&gpu_delay_filter);
	obs_register_source(&color_key_filter);
	obs_register_source(&color_grade_filter);
	obs_register_source(&sharpness_filter);
	obs_register_source(&chroma_key_filter);
	obs_register_source(&async_delay_filter);
#if SPEEXDSP_ENABLED
	obs_register_source(&noise_suppress_filter);
#endif
	obs_register_source(&invert_polarity_filter);
	obs_register_source(&noise_gate_filter);
	obs_register_source(&compressor_filter);
	obs_register_source(&limiter_filter);
	obs_register_source(&expander_filter);
	obs_register_source(&luma_key_filter);
	return true;
}