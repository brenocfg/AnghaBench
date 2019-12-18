#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ private; } ;
struct TYPE_5__ {TYPE_4__ context; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_hotkey_id ;
typedef  int /*<<< orphan*/  obs_hotkey_func ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_HOTKEY_REGISTERER_SOURCE ; 
 int /*<<< orphan*/  OBS_INVALID_HOTKEY_ID ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  obs_hotkey_register_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,char const*,char const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  obs_source_get_weak_source (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock () ; 

obs_hotkey_id obs_hotkey_register_source(obs_source_t *source, const char *name,
					 const char *description,
					 obs_hotkey_func func, void *data)
{
	if (!source || source->context.private || !lock())
		return OBS_INVALID_HOTKEY_ID;

	obs_hotkey_id id = obs_hotkey_register_internal(
		OBS_HOTKEY_REGISTERER_SOURCE,
		obs_source_get_weak_source(source), &source->context, name,
		description, func, data);

	unlock();
	return id;
}