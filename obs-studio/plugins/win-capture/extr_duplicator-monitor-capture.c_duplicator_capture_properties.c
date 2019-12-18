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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_COMBO_FORMAT_INT ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  TEXT_CAPTURE_CURSOR ; 
 int /*<<< orphan*/  TEXT_MONITOR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 scalar_t__ get_monitor_props (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 

__attribute__((used)) static obs_properties_t *duplicator_capture_properties(void *unused)
{
	int monitor_idx = 0;

	UNUSED_PARAMETER(unused);

	obs_properties_t *props = obs_properties_create();

	obs_property_t *monitors = obs_properties_add_list(
		props, "monitor", TEXT_MONITOR, OBS_COMBO_TYPE_LIST,
		OBS_COMBO_FORMAT_INT);

	obs_properties_add_bool(props, "capture_cursor", TEXT_CAPTURE_CURSOR);

	obs_enter_graphics();

	while (get_monitor_props(monitors, monitor_idx++))
		;

	obs_leave_graphics();

	return props;
}