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
struct obs_scene_item {int visible; int user_visible; int /*<<< orphan*/  actions_mutex; int /*<<< orphan*/  active_refs; int /*<<< orphan*/  source; TYPE_1__* parent; int /*<<< orphan*/  audio_actions; } ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_add_active_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_remove_active_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_atomic_load_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_visibility(struct obs_scene_item *item, bool vis)
{
	pthread_mutex_lock(&item->actions_mutex);

	da_resize(item->audio_actions, 0);

	if (os_atomic_load_long(&item->active_refs) > 0) {
		if (!vis)
			obs_source_remove_active_child(item->parent->source,
						       item->source);
	} else if (vis) {
		obs_source_add_active_child(item->parent->source, item->source);
	}

	os_atomic_set_long(&item->active_refs, vis ? 1 : 0);
	item->visible = vis;
	item->user_visible = vis;

	pthread_mutex_unlock(&item->actions_mutex);
}