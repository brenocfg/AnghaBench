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
struct gs_monitor_info {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_MONITOR ; 
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  gs_get_duplicator_monitor_info (int,struct gs_monitor_info*) ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool get_monitor_props(obs_property_t *monitor_list, int monitor_idx)
{
	struct dstr monitor_desc = {0};
	struct gs_monitor_info info;

	if (!gs_get_duplicator_monitor_info(monitor_idx, &info))
		return false;

	dstr_catf(&monitor_desc, "%s %d: %ldx%ld @ %ld,%ld", TEXT_MONITOR,
		  monitor_idx + 1, info.cx, info.cy, info.x, info.y);

	obs_property_list_add_int(monitor_list, monitor_desc.array,
				  monitor_idx);

	dstr_free(&monitor_desc);

	return true;
}