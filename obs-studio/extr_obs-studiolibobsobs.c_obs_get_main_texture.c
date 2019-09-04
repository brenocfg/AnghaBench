#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct obs_core_video {int cur_texture; int /*<<< orphan*/ ** render_textures; int /*<<< orphan*/ * textures_rendered; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int NUM_TEXTURES ; 
 TYPE_1__* obs ; 

gs_texture_t *obs_get_main_texture(void)
{
	struct obs_core_video *video = &obs->video;
	int last_tex;

	if (!obs) return NULL;

	last_tex = video->cur_texture == 0
		? NUM_TEXTURES - 1
		: video->cur_texture - 1;

	if (!video->textures_rendered[last_tex])
		return NULL;

	return video->render_textures[last_tex];
}