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
struct obs_scene_item {struct obs_scene_item* next; scalar_t__ item_render; } ;
struct obs_scene {struct obs_scene_item* first_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  gs_texrender_reset (scalar_t__) ; 
 int /*<<< orphan*/  video_lock (struct obs_scene*) ; 
 int /*<<< orphan*/  video_unlock (struct obs_scene*) ; 

__attribute__((used)) static void scene_video_tick(void *data, float seconds)
{
	struct obs_scene *scene = data;
	struct obs_scene_item *item;

	video_lock(scene);
	item = scene->first_item;
	while (item) {
		if (item->item_render)
			gs_texrender_reset(item->item_render);
		item = item->next;
	}
	video_unlock(scene);

	UNUSED_PARAMETER(seconds);
}