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
typedef  int /*<<< orphan*/  obs_hotkey_id ;
typedef  int /*<<< orphan*/  obs_hotkey_func ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_HOTKEY_REGISTERER_FRONTEND ; 
 int /*<<< orphan*/  OBS_INVALID_HOTKEY_ID ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  obs_hotkey_register_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unlock () ; 

obs_hotkey_id obs_hotkey_register_frontend(const char *name,
					   const char *description,
					   obs_hotkey_func func, void *data)
{
	if (!lock())
		return OBS_INVALID_HOTKEY_ID;

	obs_hotkey_id id = obs_hotkey_register_internal(
		OBS_HOTKEY_REGISTERER_FRONTEND, NULL, NULL, name, description,
		func, data);

	unlock();
	return id;
}