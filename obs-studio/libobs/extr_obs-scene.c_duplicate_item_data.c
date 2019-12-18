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
struct obs_scene_item {int /*<<< orphan*/  private_settings; scalar_t__ item_render; int /*<<< orphan*/  update_transform; int /*<<< orphan*/  crop; int /*<<< orphan*/  toggle_visibility; int /*<<< orphan*/  bounds; int /*<<< orphan*/  bounds_align; int /*<<< orphan*/  bounds_type; int /*<<< orphan*/  draw_transform; int /*<<< orphan*/  box_scale; int /*<<< orphan*/  box_transform; int /*<<< orphan*/  scale_filter; int /*<<< orphan*/  output_scale; int /*<<< orphan*/  last_height; int /*<<< orphan*/  last_width; int /*<<< orphan*/  align; int /*<<< orphan*/  scale; int /*<<< orphan*/  rot; int /*<<< orphan*/  pos; int /*<<< orphan*/  selected; int /*<<< orphan*/  user_visible; struct obs_scene* parent; } ;
struct obs_scene {TYPE_2__* source; } ;
typedef  int /*<<< orphan*/  obs_data_array_t ;
struct TYPE_3__ {int /*<<< orphan*/  private; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  GS_ZS_NONE ; 
 scalar_t__ gs_texrender_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ item_texture_enabled (struct obs_scene_item*) ; 
 int /*<<< orphan*/  obs_data_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_hotkey_pair_load (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_hotkey_pair_save (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_sceneitem_set_crop (struct obs_scene_item*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_visibility (struct obs_scene_item*,int) ; 

__attribute__((used)) static inline void duplicate_item_data(struct obs_scene_item *dst,
				       struct obs_scene_item *src,
				       bool defer_texture_update,
				       bool duplicate_hotkeys,
				       bool duplicate_private_data)
{
	struct obs_scene *dst_scene = dst->parent;

	if (!src->user_visible)
		set_visibility(dst, false);

	dst->selected = src->selected;
	dst->pos = src->pos;
	dst->rot = src->rot;
	dst->scale = src->scale;
	dst->align = src->align;
	dst->last_width = src->last_width;
	dst->last_height = src->last_height;
	dst->output_scale = src->output_scale;
	dst->scale_filter = src->scale_filter;
	dst->box_transform = src->box_transform;
	dst->box_scale = src->box_scale;
	dst->draw_transform = src->draw_transform;
	dst->bounds_type = src->bounds_type;
	dst->bounds_align = src->bounds_align;
	dst->bounds = src->bounds;

	if (duplicate_hotkeys && !dst_scene->source->context.private) {
		obs_data_array_t *data0 = NULL;
		obs_data_array_t *data1 = NULL;

		obs_hotkey_pair_save(src->toggle_visibility, &data0, &data1);
		obs_hotkey_pair_load(dst->toggle_visibility, data0, data1);

		obs_data_array_release(data0);
		obs_data_array_release(data1);
	}

	obs_sceneitem_set_crop(dst, &src->crop);

	if (defer_texture_update) {
		os_atomic_set_bool(&dst->update_transform, true);
	} else {
		if (!dst->item_render && item_texture_enabled(dst)) {
			obs_enter_graphics();
			dst->item_render =
				gs_texrender_create(GS_RGBA, GS_ZS_NONE);
			obs_leave_graphics();
		}
	}

	if (duplicate_private_data) {
		obs_data_apply(dst->private_settings, src->private_settings);
	}
}