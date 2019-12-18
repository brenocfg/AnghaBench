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
 int /*<<< orphan*/  EXCLUDE_MINIMIZED ; 
 int /*<<< orphan*/  OBS_COMBO_FORMAT_INT ; 
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  TEXT_CAPTURE_CURSOR ; 
 int /*<<< orphan*/  TEXT_COMPATIBILITY ; 
 int /*<<< orphan*/  TEXT_MATCH_CLASS ; 
 int /*<<< orphan*/  TEXT_MATCH_EXE ; 
 int /*<<< orphan*/  TEXT_MATCH_PRIORITY ; 
 int /*<<< orphan*/  TEXT_MATCH_TITLE ; 
 int /*<<< orphan*/  TEXT_WINDOW ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  WINDOW_PRIORITY_CLASS ; 
 int /*<<< orphan*/  WINDOW_PRIORITY_EXE ; 
 int /*<<< orphan*/  WINDOW_PRIORITY_TITLE ; 
 int /*<<< orphan*/  fill_window_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static obs_properties_t *wc_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *ppts = obs_properties_create();
	obs_property_t *p;

	p = obs_properties_add_list(ppts, "window", TEXT_WINDOW,
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	fill_window_list(p, EXCLUDE_MINIMIZED, NULL);

	p = obs_properties_add_list(ppts, "priority", TEXT_MATCH_PRIORITY,
				    OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
	obs_property_list_add_int(p, TEXT_MATCH_TITLE, WINDOW_PRIORITY_TITLE);
	obs_property_list_add_int(p, TEXT_MATCH_CLASS, WINDOW_PRIORITY_CLASS);
	obs_property_list_add_int(p, TEXT_MATCH_EXE, WINDOW_PRIORITY_EXE);

	obs_properties_add_bool(ppts, "cursor", TEXT_CAPTURE_CURSOR);

	obs_properties_add_bool(ppts, "compatibility", TEXT_COMPATIBILITY);

	return ppts;
}