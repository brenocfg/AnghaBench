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
struct fade_to_color_info {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fade_to_color_callback ; 
 int /*<<< orphan*/  obs_transition_video_render (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fade_to_color_video_render(void *data, gs_effect_t *effect)
{
	struct fade_to_color_info *fade_to_color = data;
	obs_transition_video_render(fade_to_color->source,
				    fade_to_color_callback);
	UNUSED_PARAMETER(effect);
}