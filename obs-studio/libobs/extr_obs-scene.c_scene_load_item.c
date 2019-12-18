#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_9__ {void* bottom; void* right; void* top; void* left; } ;
struct obs_scene_item {int is_group; float rot; int bounds_type; int /*<<< orphan*/ * item_render; int /*<<< orphan*/  scale_filter; TYPE_2__ crop; int /*<<< orphan*/  bounds; void* bounds_align; scalar_t__ private_settings; int /*<<< orphan*/  scale; int /*<<< orphan*/  pos; void* align; scalar_t__ id; } ;
struct obs_scene {int /*<<< orphan*/  source; } ;
struct TYPE_8__ {scalar_t__ id; } ;
struct TYPE_10__ {TYPE_1__ info; } ;
typedef  TYPE_3__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  enum obs_bounds_type { ____Placeholder_obs_bounds_type } obs_bounds_type ;
struct TYPE_11__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  GS_ZS_NONE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int OBS_ALIGN_LEFT ; 
 int OBS_ALIGN_TOP ; 
 int /*<<< orphan*/  OBS_SCALE_AREA ; 
 int /*<<< orphan*/  OBS_SCALE_BICUBIC ; 
 int /*<<< orphan*/  OBS_SCALE_BILINEAR ; 
 int /*<<< orphan*/  OBS_SCALE_DISABLE ; 
 int /*<<< orphan*/  OBS_SCALE_LANCZOS ; 
 int /*<<< orphan*/  OBS_SCALE_POINT ; 
 scalar_t__ astrcmpi (char const*,char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 TYPE_7__ group_info ; 
 int /*<<< orphan*/ * gs_texrender_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texrender_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ item_texture_enabled (struct obs_scene_item*) ; 
 scalar_t__ obs_data_create () ; 
 int obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_double (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_obj (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_vec2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ obs_data_has_user_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (scalar_t__) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 TYPE_3__* obs_get_source_by_name (char const*) ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 struct obs_scene_item* obs_scene_add (struct obs_scene*,TYPE_3__*) ; 
 int /*<<< orphan*/  obs_sceneitem_set_locked (struct obs_scene_item*,int) ; 
 int /*<<< orphan*/  obs_source_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_release (TYPE_3__*) ; 
 int /*<<< orphan*/  set_visibility (struct obs_scene_item*,int) ; 
 int /*<<< orphan*/  update_item_transform (struct obs_scene_item*,int) ; 

__attribute__((used)) static void scene_load_item(struct obs_scene *scene, obs_data_t *item_data)
{
	const char *name = obs_data_get_string(item_data, "name");
	obs_source_t *source;
	const char *scale_filter_str;
	struct obs_scene_item *item;
	bool visible;
	bool lock;

	if (obs_data_get_bool(item_data, "group_item_backup"))
		return;

	source = obs_get_source_by_name(name);
	if (!source) {
		blog(LOG_WARNING,
		     "[scene_load_item] Source %s not "
		     "found!",
		     name);
		return;
	}

	item = obs_scene_add(scene, source);
	if (!item) {
		blog(LOG_WARNING,
		     "[scene_load_item] Could not add source '%s' "
		     "to scene '%s'!",
		     name, obs_source_get_name(scene->source));

		obs_source_release(source);
		return;
	}

	item->is_group = source->info.id == group_info.id;

	obs_data_set_default_int(item_data, "align",
				 OBS_ALIGN_TOP | OBS_ALIGN_LEFT);

	if (obs_data_has_user_value(item_data, "id"))
		item->id = obs_data_get_int(item_data, "id");

	item->rot = (float)obs_data_get_double(item_data, "rot");
	item->align = (uint32_t)obs_data_get_int(item_data, "align");
	visible = obs_data_get_bool(item_data, "visible");
	lock = obs_data_get_bool(item_data, "locked");
	obs_data_get_vec2(item_data, "pos", &item->pos);
	obs_data_get_vec2(item_data, "scale", &item->scale);

	obs_data_release(item->private_settings);
	item->private_settings =
		obs_data_get_obj(item_data, "private_settings");
	if (!item->private_settings)
		item->private_settings = obs_data_create();

	set_visibility(item, visible);
	obs_sceneitem_set_locked(item, lock);

	item->bounds_type = (enum obs_bounds_type)obs_data_get_int(
		item_data, "bounds_type");
	item->bounds_align =
		(uint32_t)obs_data_get_int(item_data, "bounds_align");
	obs_data_get_vec2(item_data, "bounds", &item->bounds);

	item->crop.left = (uint32_t)obs_data_get_int(item_data, "crop_left");
	item->crop.top = (uint32_t)obs_data_get_int(item_data, "crop_top");
	item->crop.right = (uint32_t)obs_data_get_int(item_data, "crop_right");
	item->crop.bottom =
		(uint32_t)obs_data_get_int(item_data, "crop_bottom");

	scale_filter_str = obs_data_get_string(item_data, "scale_filter");
	item->scale_filter = OBS_SCALE_DISABLE;

	if (scale_filter_str) {
		if (astrcmpi(scale_filter_str, "point") == 0)
			item->scale_filter = OBS_SCALE_POINT;
		else if (astrcmpi(scale_filter_str, "bilinear") == 0)
			item->scale_filter = OBS_SCALE_BILINEAR;
		else if (astrcmpi(scale_filter_str, "bicubic") == 0)
			item->scale_filter = OBS_SCALE_BICUBIC;
		else if (astrcmpi(scale_filter_str, "lanczos") == 0)
			item->scale_filter = OBS_SCALE_LANCZOS;
		else if (astrcmpi(scale_filter_str, "area") == 0)
			item->scale_filter = OBS_SCALE_AREA;
	}

	if (item->item_render && !item_texture_enabled(item)) {
		obs_enter_graphics();
		gs_texrender_destroy(item->item_render);
		item->item_render = NULL;
		obs_leave_graphics();

	} else if (!item->item_render && item_texture_enabled(item)) {
		obs_enter_graphics();
		item->item_render = gs_texrender_create(GS_RGBA, GS_ZS_NONE);
		obs_leave_graphics();
	}

	obs_source_release(source);

	update_item_transform(item, false);
}