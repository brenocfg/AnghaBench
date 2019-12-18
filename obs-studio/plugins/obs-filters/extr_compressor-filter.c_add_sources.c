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
typedef  int uint32_t ;
struct sidechain_prop_info {int /*<<< orphan*/  sources; int /*<<< orphan*/ * parent; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_AUDIO ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ ,char const*,char const*) ; 
 char* obs_source_get_name (int /*<<< orphan*/ *) ; 
 int obs_source_get_output_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool add_sources(void *data, obs_source_t *source)
{
	struct sidechain_prop_info *info = data;
	uint32_t caps = obs_source_get_output_flags(source);

	if (source == info->parent)
		return true;
	if ((caps & OBS_SOURCE_AUDIO) == 0)
		return true;

	const char *name = obs_source_get_name(source);
	obs_property_list_add_string(info->sources, name, name);
	return true;
}