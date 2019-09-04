#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct obs_core_hotkeys {int /*<<< orphan*/  signals; int /*<<< orphan*/  mutex; TYPE_1__* platform_context; } ;
struct TYPE_6__ {scalar_t__ layout_data; int /*<<< orphan*/  tis; } ;
typedef  TYPE_1__ obs_hotkeys_platform_t ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ calldata_t ;
typedef  void const* CFStringRef ;
typedef  void const* CFNotificationCenterRef ;
typedef  void const* CFDictionaryRef ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void const*) ; 
 int /*<<< orphan*/  hotkeys_release (TYPE_1__*) ; 
 scalar_t__ init_hotkeys_platform (TYPE_1__**) ; 
 int /*<<< orphan*/  log_layout_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 

__attribute__((used)) static void input_method_changed(CFNotificationCenterRef nc, void *observer,
		CFStringRef name, const void *object, CFDictionaryRef user_info)
{
	UNUSED_PARAMETER(nc);
	UNUSED_PARAMETER(name);
	UNUSED_PARAMETER(object);
	UNUSED_PARAMETER(user_info);

	struct obs_core_hotkeys *hotkeys = observer;
	obs_hotkeys_platform_t *new_plat;

	if (init_hotkeys_platform(&new_plat)) {
		obs_hotkeys_platform_t *plat;

		pthread_mutex_lock(&hotkeys->mutex);
		plat = hotkeys->platform_context;

		if (new_plat && plat &&
				new_plat->layout_data == plat->layout_data) {
			pthread_mutex_unlock(&hotkeys->mutex);
			hotkeys_release(new_plat);
			return;
		}

		hotkeys->platform_context = new_plat;
		if (new_plat)
			log_layout_name(new_plat->tis);
		pthread_mutex_unlock(&hotkeys->mutex);

		calldata_t params = {0};
		signal_handler_signal(hotkeys->signals,
				"hotkey_layout_change", &params);
		if (plat)
			hotkeys_release(plat);
	}
}