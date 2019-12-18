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
struct obs_source_info {int /*<<< orphan*/  output_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_SOURCE_CAP_DISABLED ; 
 struct obs_source_info* get_source_info (char const*) ; 

void obs_enable_source_type(const char *name, bool enable)
{
	struct obs_source_info *info = get_source_info(name);
	if (!info)
		return;

	if (enable)
		info->output_flags &= ~OBS_SOURCE_CAP_DISABLED;
	else
		info->output_flags |= OBS_SOURCE_CAP_DISABLED;
}