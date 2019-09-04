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
struct obs_core_video {int output_width; int base_width; int output_height; int base_height; int scale_type; int /*<<< orphan*/ * bicubic_effect; int /*<<< orphan*/ * lanczos_effect; int /*<<< orphan*/ * default_effect; int /*<<< orphan*/ * bilinear_lowres_effect; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
#define  OBS_SCALE_BICUBIC 130 
#define  OBS_SCALE_BILINEAR 129 
#define  OBS_SCALE_LANCZOS 128 

__attribute__((used)) static inline gs_effect_t *get_scale_effect_internal(
		struct obs_core_video *video)
{
	/* if the dimension is under half the size of the original image,
	 * bicubic/lanczos can't sample enough pixels to create an accurate
	 * image, so use the bilinear low resolution effect instead */
	if (video->output_width  < (video->base_width  / 2) &&
	    video->output_height < (video->base_height / 2)) {
		return video->bilinear_lowres_effect;
	}

	switch (video->scale_type) {
	case OBS_SCALE_BILINEAR: return video->default_effect;
	case OBS_SCALE_LANCZOS:  return video->lanczos_effect;
	case OBS_SCALE_BICUBIC:
	default:;
	}

	return video->bicubic_effect;
}