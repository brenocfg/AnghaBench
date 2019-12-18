#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gs_effect_t ;
typedef  enum obs_deinterlace_mode { ____Placeholder_obs_deinterlace_mode } obs_deinterlace_mode ;
struct TYPE_3__ {int /*<<< orphan*/  deinterlace_yadif_2x_effect; int /*<<< orphan*/  deinterlace_yadif_effect; int /*<<< orphan*/  deinterlace_linear_2x_effect; int /*<<< orphan*/  deinterlace_linear_effect; int /*<<< orphan*/  deinterlace_blend_2x_effect; int /*<<< orphan*/  deinterlace_blend_effect; int /*<<< orphan*/  deinterlace_discard_2x_effect; int /*<<< orphan*/  deinterlace_discard_effect; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
#define  OBS_DEINTERLACE_MODE_BLEND 136 
#define  OBS_DEINTERLACE_MODE_BLEND_2X 135 
#define  OBS_DEINTERLACE_MODE_DISABLE 134 
#define  OBS_DEINTERLACE_MODE_DISCARD 133 
#define  OBS_DEINTERLACE_MODE_LINEAR 132 
#define  OBS_DEINTERLACE_MODE_LINEAR_2X 131 
#define  OBS_DEINTERLACE_MODE_RETRO 130 
#define  OBS_DEINTERLACE_MODE_YADIF 129 
#define  OBS_DEINTERLACE_MODE_YADIF_2X 128 
 TYPE_2__* obs ; 
 int /*<<< orphan*/ * obs_load_effect (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline gs_effect_t *get_effect(enum obs_deinterlace_mode mode)
{
	switch (mode) {
	case OBS_DEINTERLACE_MODE_DISABLE:
		return NULL;
	case OBS_DEINTERLACE_MODE_DISCARD:
		return obs_load_effect(&obs->video.deinterlace_discard_effect,
				       "deinterlace_discard.effect");
	case OBS_DEINTERLACE_MODE_RETRO:
		return obs_load_effect(
			&obs->video.deinterlace_discard_2x_effect,
			"deinterlace_discard_2x.effect");
	case OBS_DEINTERLACE_MODE_BLEND:
		return obs_load_effect(&obs->video.deinterlace_blend_effect,
				       "deinterlace_blend.effect");
	case OBS_DEINTERLACE_MODE_BLEND_2X:
		return obs_load_effect(&obs->video.deinterlace_blend_2x_effect,
				       "deinterlace_blend_2x.effect");
	case OBS_DEINTERLACE_MODE_LINEAR:
		return obs_load_effect(&obs->video.deinterlace_linear_effect,
				       "deinterlace_linear.effect");
	case OBS_DEINTERLACE_MODE_LINEAR_2X:
		return obs_load_effect(&obs->video.deinterlace_linear_2x_effect,
				       "deinterlace_linear_2x.effect");
	case OBS_DEINTERLACE_MODE_YADIF:
		return obs_load_effect(&obs->video.deinterlace_yadif_effect,
				       "deinterlace_yadif.effect");
	case OBS_DEINTERLACE_MODE_YADIF_2X:
		return obs_load_effect(&obs->video.deinterlace_yadif_2x_effect,
				       "deinterlace_yadif_2x.effect");
	}

	return NULL;
}