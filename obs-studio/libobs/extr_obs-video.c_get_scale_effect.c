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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_core_video {int /*<<< orphan*/ * default_effect; int /*<<< orphan*/ * bicubic_effect; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_scale_effect_internal (struct obs_core_video*) ; 
 scalar_t__ resolution_close (struct obs_core_video*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline gs_effect_t *get_scale_effect(struct obs_core_video *video,
					    uint32_t width, uint32_t height)
{
	if (resolution_close(video, width, height)) {
		return video->default_effect;
	} else {
		/* if the scale method couldn't be loaded, use either bicubic
		 * or bilinear by default */
		gs_effect_t *effect = get_scale_effect_internal(video);
		if (!effect)
			effect = !!video->bicubic_effect
					 ? video->bicubic_effect
					 : video->default_effect;
		return effect;
	}
}