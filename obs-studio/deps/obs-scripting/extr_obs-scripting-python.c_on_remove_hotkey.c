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
struct TYPE_2__ {int /*<<< orphan*/  extra; } ;
struct python_obs_callback {TYPE_1__ base; } ;
typedef  scalar_t__ obs_hotkey_id ;

/* Variables and functions */
 scalar_t__ OBS_INVALID_HOTKEY_ID ; 
 int /*<<< orphan*/  calldata_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  defer_call_post (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  defer_hotkey_unregister ; 

__attribute__((used)) static void on_remove_hotkey(void *p_cb)
{
	struct python_obs_callback *cb = p_cb;
	obs_hotkey_id id = (obs_hotkey_id)calldata_int(&cb->base.extra, "id");

	if (id != OBS_INVALID_HOTKEY_ID)
		defer_call_post(defer_hotkey_unregister, (void *)(uintptr_t)id);
}