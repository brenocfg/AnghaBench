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
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_array (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * save_hotkey (TYPE_1__*) ; 

__attribute__((used)) static inline bool enum_save_hotkey(void *data, size_t idx,
				    obs_hotkey_t *hotkey)
{
	UNUSED_PARAMETER(idx);

	obs_data_array_t *hotkey_data = save_hotkey(hotkey);
	obs_data_set_array(data, hotkey->name, hotkey_data);
	obs_data_array_release(hotkey_data);
	return true;
}