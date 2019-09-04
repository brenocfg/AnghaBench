#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  hotkey_signal (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_binding (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t obs_data_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_array_item (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void load_bindings(obs_hotkey_t *hotkey, obs_data_array_t *data)
{
	const size_t count = obs_data_array_count(data);
	for (size_t i = 0; i < count; i++) {
		obs_data_t *item = obs_data_array_item(data, i);
		load_binding(hotkey, item);
		obs_data_release(item);
	}

	hotkey_signal("hotkey_bindings_changed", hotkey);
}