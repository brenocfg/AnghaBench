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
struct luma_wipe_info {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luma_wipe_callback ; 
 int /*<<< orphan*/  obs_transition_video_render (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void luma_wipe_video_render(void *data, gs_effect_t *effect)
{
	struct luma_wipe_info *lwipe = data;
	obs_transition_video_render(lwipe->source, luma_wipe_callback);
	UNUSED_PARAMETER(effect);
}