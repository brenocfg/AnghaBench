#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  audio_actions; scalar_t__ source; int /*<<< orphan*/  actions_mutex; int /*<<< orphan*/  toggle_visibility; int /*<<< orphan*/  private_settings; scalar_t__ item_render; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texrender_destroy (scalar_t__) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_hotkey_pair_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_source_get_signal_handler (scalar_t__) ; 
 int /*<<< orphan*/  obs_source_release (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceneitem_renamed ; 
 int /*<<< orphan*/  signal_handler_disconnect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void obs_sceneitem_destroy(obs_sceneitem_t *item)
{
	if (item) {
		if (item->item_render) {
			obs_enter_graphics();
			gs_texrender_destroy(item->item_render);
			obs_leave_graphics();
		}
		obs_data_release(item->private_settings);
		obs_hotkey_pair_unregister(item->toggle_visibility);
		pthread_mutex_destroy(&item->actions_mutex);
		signal_handler_disconnect(
			obs_source_get_signal_handler(item->source), "rename",
			sceneitem_renamed, item);
		if (item->source)
			obs_source_release(item->source);
		da_free(item->audio_actions);
		bfree(item);
	}
}