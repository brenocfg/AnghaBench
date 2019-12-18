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
struct TYPE_4__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_hotkey_pair_id ;
typedef  int /*<<< orphan*/  obs_hotkey_active_func ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_HOTKEY_REGISTERER_SOURCE ; 
 int /*<<< orphan*/  OBS_INVALID_HOTKEY_PAIR_ID ; 
 int /*<<< orphan*/  register_hotkey_pair_internal (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  weak_source_ref ; 

obs_hotkey_pair_id obs_hotkey_pair_register_source(
	obs_source_t *source, const char *name0, const char *description0,
	const char *name1, const char *description1,
	obs_hotkey_active_func func0, obs_hotkey_active_func func1, void *data0,
	void *data1)
{
	if (!source)
		return OBS_INVALID_HOTKEY_PAIR_ID;
	return register_hotkey_pair_internal(OBS_HOTKEY_REGISTERER_SOURCE,
					     source, weak_source_ref,
					     &source->context, name0,
					     description0, name1, description1,
					     func0, func1, data0, data1);
}