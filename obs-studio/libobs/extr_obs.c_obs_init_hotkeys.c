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
struct obs_core_hotkeys {int hotkey_thread_initialized; int /*<<< orphan*/  hotkey_thread; int /*<<< orphan*/  stop_event; int /*<<< orphan*/  mutex; void* sceneitem_hide; void* sceneitem_show; void* push_to_talk; void* push_to_mute; void* unmute; void* mute; int /*<<< orphan*/  name_map_init_token; int /*<<< orphan*/  signals; int /*<<< orphan*/  hotkeys; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_2__ {int /*<<< orphan*/  signals; struct obs_core_hotkeys hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  OS_EVENT_TYPE_MANUAL ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* bstrdup (char*) ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_hotkey_thread ; 
 int /*<<< orphan*/  obs_hotkeys_platform_init (struct obs_core_hotkeys*) ; 
 int /*<<< orphan*/  obs_pthread_once_init_token ; 
 scalar_t__ os_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool obs_init_hotkeys(void)
{
	struct obs_core_hotkeys *hotkeys = &obs->hotkeys;
	pthread_mutexattr_t attr;
	bool success = false;

	assert(hotkeys != NULL);

	da_init(hotkeys->hotkeys);
	hotkeys->signals = obs->signals;
	hotkeys->name_map_init_token = obs_pthread_once_init_token;
	hotkeys->mute = bstrdup("Mute");
	hotkeys->unmute = bstrdup("Unmute");
	hotkeys->push_to_mute = bstrdup("Push-to-mute");
	hotkeys->push_to_talk = bstrdup("Push-to-talk");
	hotkeys->sceneitem_show = bstrdup("Show '%1'");
	hotkeys->sceneitem_hide = bstrdup("Hide '%1'");

	if (!obs_hotkeys_platform_init(hotkeys))
		return false;

	if (pthread_mutexattr_init(&attr) != 0)
		return false;
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
		goto fail;
	if (pthread_mutex_init(&hotkeys->mutex, &attr) != 0)
		goto fail;

	if (os_event_init(&hotkeys->stop_event, OS_EVENT_TYPE_MANUAL) != 0)
		goto fail;
	if (pthread_create(&hotkeys->hotkey_thread, NULL, obs_hotkey_thread,
			   NULL))
		goto fail;

	hotkeys->hotkey_thread_initialized = true;

	success = true;

fail:
	pthread_mutexattr_destroy(&attr);
	return success;
}