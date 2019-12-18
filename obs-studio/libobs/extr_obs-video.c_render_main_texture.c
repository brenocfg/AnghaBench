#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vec4 {int dummy; } ;
struct obs_core_video {int texture_rendered; int /*<<< orphan*/  base_height; int /*<<< orphan*/  base_width; int /*<<< orphan*/  render_texture; } ;
struct draw_callback {int /*<<< orphan*/  param; int /*<<< orphan*/  (* draw ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {size_t num; struct draw_callback* array; } ;
struct TYPE_5__ {int /*<<< orphan*/  main_view; int /*<<< orphan*/  draw_callbacks_mutex; TYPE_1__ draw_callbacks; } ;
struct TYPE_6__ {TYPE_2__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_CLEAR_COLOR ; 
 int /*<<< orphan*/  GS_DEBUG_COLOR_MAIN_TEXTURE ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_BEGIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_END () ; 
 int /*<<< orphan*/  gs_clear (int /*<<< orphan*/ ,struct vec4*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_set_render_target (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/  obs_view_render (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_main_texture_name ; 
 int /*<<< orphan*/  set_render_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec4_set (struct vec4*,float,float,float,float) ; 

__attribute__((used)) static inline void render_main_texture(struct obs_core_video *video)
{
	profile_start(render_main_texture_name);
	GS_DEBUG_MARKER_BEGIN(GS_DEBUG_COLOR_MAIN_TEXTURE,
			      render_main_texture_name);

	struct vec4 clear_color;
	vec4_set(&clear_color, 0.0f, 0.0f, 0.0f, 0.0f);

	gs_set_render_target(video->render_texture, NULL);
	gs_clear(GS_CLEAR_COLOR, &clear_color, 1.0f, 0);

	set_render_size(video->base_width, video->base_height);

	pthread_mutex_lock(&obs->data.draw_callbacks_mutex);

	for (size_t i = obs->data.draw_callbacks.num; i > 0; i--) {
		struct draw_callback *callback;
		callback = obs->data.draw_callbacks.array + (i - 1);

		callback->draw(callback->param, video->base_width,
			       video->base_height);
	}

	pthread_mutex_unlock(&obs->data.draw_callbacks_mutex);

	obs_view_render(&obs->data.main_view);

	video->texture_rendered = true;

	GS_DEBUG_MARKER_END();
	profile_end(render_main_texture_name);
}