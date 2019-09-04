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
typedef  enum obs_base_effect { ____Placeholder_obs_base_effect } obs_base_effect ;
struct TYPE_3__ {int /*<<< orphan*/ * premultiplied_alpha_effect; int /*<<< orphan*/ * bilinear_lowres_effect; int /*<<< orphan*/ * area_effect; int /*<<< orphan*/ * lanczos_effect; int /*<<< orphan*/ * bicubic_effect; int /*<<< orphan*/ * repeat_effect; int /*<<< orphan*/ * solid_effect; int /*<<< orphan*/ * opaque_effect; int /*<<< orphan*/ * default_rect_effect; int /*<<< orphan*/ * default_effect; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
#define  OBS_EFFECT_AREA 137 
#define  OBS_EFFECT_BICUBIC 136 
#define  OBS_EFFECT_BILINEAR_LOWRES 135 
#define  OBS_EFFECT_DEFAULT 134 
#define  OBS_EFFECT_DEFAULT_RECT 133 
#define  OBS_EFFECT_LANCZOS 132 
#define  OBS_EFFECT_OPAQUE 131 
#define  OBS_EFFECT_PREMULTIPLIED_ALPHA 130 
#define  OBS_EFFECT_REPEAT 129 
#define  OBS_EFFECT_SOLID 128 
 TYPE_2__* obs ; 

gs_effect_t *obs_get_base_effect(enum obs_base_effect effect)
{
	if (!obs) return NULL;

	switch (effect) {
	case OBS_EFFECT_DEFAULT:
		return obs->video.default_effect;
	case OBS_EFFECT_DEFAULT_RECT:
		return obs->video.default_rect_effect;
	case OBS_EFFECT_OPAQUE:
		return obs->video.opaque_effect;
	case OBS_EFFECT_SOLID:
		return obs->video.solid_effect;
	case OBS_EFFECT_REPEAT:
		return obs->video.repeat_effect;
	case OBS_EFFECT_BICUBIC:
		return obs->video.bicubic_effect;
	case OBS_EFFECT_LANCZOS:
		return obs->video.lanczos_effect;
	case OBS_EFFECT_AREA:
		return obs->video.area_effect;
	case OBS_EFFECT_BILINEAR_LOWRES:
		return obs->video.bilinear_lowres_effect;
	case OBS_EFFECT_PREMULTIPLIED_ALPHA:
		return obs->video.premultiplied_alpha_effect;
	}

	return NULL;
}