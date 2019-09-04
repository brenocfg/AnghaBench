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
struct slideshow {int dummy; } ;
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_transition (struct slideshow*) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_video_render (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ss_video_render(void *data, gs_effect_t *effect)
{
	struct slideshow *ss = data;
	obs_source_t *transition = get_transition(ss);

	if (transition) {
		obs_source_video_render(transition);
		obs_source_release(transition);
	}

	UNUSED_PARAMETER(effect);
}