#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ obs_hotkey_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  load_bindings (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_get_array (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool enum_load_bindings(void *data, size_t idx,
				      obs_hotkey_t *hotkey)
{
	UNUSED_PARAMETER(idx);

	obs_data_array_t *hotkey_data = obs_data_get_array(data, hotkey->name);
	if (!hotkey_data)
		return true;

	load_bindings(hotkey, hotkey_data);
	obs_data_array_release(hotkey_data);
	return true;
}