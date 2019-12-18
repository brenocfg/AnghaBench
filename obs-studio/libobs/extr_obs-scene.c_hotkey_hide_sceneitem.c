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
struct TYPE_5__ {scalar_t__ user_visible; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/ * obs_hotkey_pair_id ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_sceneitem_release (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_sceneitem_set_visible (TYPE_1__*,int) ; 
 TYPE_1__* sceneitem_get_ref (void*) ; 

__attribute__((used)) static bool hotkey_hide_sceneitem(void *data, obs_hotkey_pair_id id,
				  obs_hotkey_t *hotkey, bool pressed)
{
	UNUSED_PARAMETER(id);
	UNUSED_PARAMETER(hotkey);

	obs_sceneitem_t *si = sceneitem_get_ref(data);
	if (pressed && si && si->user_visible) {
		obs_sceneitem_set_visible(si, false);
		obs_sceneitem_release(si);
		return true;
	}

	obs_sceneitem_release(si);
	return false;
}