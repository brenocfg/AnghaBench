#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct obs_scene_item {int ref; int align; int user_visible; int locked; int is_group; int visible; struct obs_scene_item* prev; struct obs_scene_item* next; int /*<<< orphan*/  item_render; int /*<<< orphan*/  audio_actions; int /*<<< orphan*/  box_transform; int /*<<< orphan*/  draw_transform; int /*<<< orphan*/  scale; int /*<<< orphan*/  active_refs; int /*<<< orphan*/  toggle_visibility; int /*<<< orphan*/  private_settings; int /*<<< orphan*/  actions_mutex; TYPE_4__* parent; scalar_t__ id; TYPE_3__* source; } ;
struct item_action {int visible; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_18__ {scalar_t__ id; } ;
struct TYPE_20__ {TYPE_1__ info; } ;
typedef  TYPE_3__ obs_source_t ;
typedef  struct obs_scene_item obs_sceneitem_t ;
struct TYPE_21__ {TYPE_9__* source; struct obs_scene_item* first_item; scalar_t__ id_counter; } ;
typedef  TYPE_4__ obs_scene_t ;
struct TYPE_19__ {int /*<<< orphan*/  private; } ;
struct TYPE_22__ {TYPE_2__ context; } ;
struct TYPE_17__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  GS_ZS_NONE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int OBS_ALIGN_LEFT ; 
 int OBS_ALIGN_TOP ; 
 int /*<<< orphan*/  OBS_INVALID_HOTKEY_PAIR_ID ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct obs_scene_item* bzalloc (int) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct item_action*) ; 
 int /*<<< orphan*/  full_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  full_unlock (TYPE_4__*) ; 
 TYPE_14__ group_info ; 
 int /*<<< orphan*/  gs_texrender_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_hotkeys (TYPE_4__*,struct obs_scene_item*,int /*<<< orphan*/ ) ; 
 scalar_t__ item_texture_enabled (struct obs_scene_item*) ; 
 int /*<<< orphan*/  matrix4_identity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_create () ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_source_add_active_child (TYPE_9__*,TYPE_3__*) ; 
 int /*<<< orphan*/  obs_source_addref (TYPE_3__*) ; 
 int /*<<< orphan*/  obs_source_get_name (TYPE_3__*) ; 
 int /*<<< orphan*/  obs_source_get_signal_handler (TYPE_3__*) ; 
 int /*<<< orphan*/  os_atomic_set_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceneitem_renamed ; 
 int /*<<< orphan*/  signal_handler_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct obs_scene_item*) ; 
 scalar_t__ source_has_audio (TYPE_3__*) ; 
 int /*<<< orphan*/  vec2_set (int /*<<< orphan*/ *,float,float) ; 

__attribute__((used)) static obs_sceneitem_t *obs_scene_add_internal(obs_scene_t *scene,
					       obs_source_t *source,
					       obs_sceneitem_t *insert_after)
{
	struct obs_scene_item *last;
	struct obs_scene_item *item;
	pthread_mutex_t mutex;

	struct item_action action = {.visible = true,
				     .timestamp = os_gettime_ns()};

	if (!scene)
		return NULL;

	if (!source) {
		blog(LOG_ERROR, "Tried to add a NULL source to a scene");
		return NULL;
	}

	if (pthread_mutex_init(&mutex, NULL) != 0) {
		blog(LOG_WARNING, "Failed to create scene item mutex");
		return NULL;
	}

	if (!obs_source_add_active_child(scene->source, source)) {
		blog(LOG_WARNING, "Failed to add source to scene due to "
				  "infinite source recursion");
		pthread_mutex_destroy(&mutex);
		return NULL;
	}

	item = bzalloc(sizeof(struct obs_scene_item));
	item->source = source;
	item->id = ++scene->id_counter;
	item->parent = scene;
	item->ref = 1;
	item->align = OBS_ALIGN_TOP | OBS_ALIGN_LEFT;
	item->actions_mutex = mutex;
	item->user_visible = true;
	item->locked = false;
	item->is_group = source->info.id == group_info.id;
	item->private_settings = obs_data_create();
	item->toggle_visibility = OBS_INVALID_HOTKEY_PAIR_ID;
	os_atomic_set_long(&item->active_refs, 1);
	vec2_set(&item->scale, 1.0f, 1.0f);
	matrix4_identity(&item->draw_transform);
	matrix4_identity(&item->box_transform);

	obs_source_addref(source);

	if (source_has_audio(source)) {
		item->visible = false;
		da_push_back(item->audio_actions, &action);
	} else {
		item->visible = true;
	}

	if (item_texture_enabled(item)) {
		obs_enter_graphics();
		item->item_render = gs_texrender_create(GS_RGBA, GS_ZS_NONE);
		obs_leave_graphics();
	}

	full_lock(scene);

	if (insert_after) {
		obs_sceneitem_t *next = insert_after->next;
		if (next)
			next->prev = item;
		item->next = insert_after->next;
		item->prev = insert_after;
		insert_after->next = item;
	} else {
		last = scene->first_item;
		if (!last) {
			scene->first_item = item;
		} else {
			while (last->next)
				last = last->next;

			last->next = item;
			item->prev = last;
		}
	}

	full_unlock(scene);

	if (!scene->source->context.private)
		init_hotkeys(scene, item, obs_source_get_name(source));

	signal_handler_connect(obs_source_get_signal_handler(source), "rename",
			       sceneitem_renamed, item);

	return item;
}