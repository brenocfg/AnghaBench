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
struct obs_core_hotkeys {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sceneitem_hide; int /*<<< orphan*/  sceneitem_show; int /*<<< orphan*/  push_to_talk; int /*<<< orphan*/  push_to_mute; int /*<<< orphan*/  unmute; int /*<<< orphan*/  mute; } ;
struct TYPE_2__ {struct obs_core_hotkeys hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_hotkey_name_map_free () ; 
 int /*<<< orphan*/  obs_hotkeys_platform_free (struct obs_core_hotkeys*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void obs_free_hotkeys(void)
{
	struct obs_core_hotkeys *hotkeys = &obs->hotkeys;

	bfree(hotkeys->mute);
	bfree(hotkeys->unmute);
	bfree(hotkeys->push_to_mute);
	bfree(hotkeys->push_to_talk);
	bfree(hotkeys->sceneitem_show);
	bfree(hotkeys->sceneitem_hide);

	obs_hotkey_name_map_free();

	obs_hotkeys_platform_free(hotkeys);
	pthread_mutex_destroy(&hotkeys->mutex);
}