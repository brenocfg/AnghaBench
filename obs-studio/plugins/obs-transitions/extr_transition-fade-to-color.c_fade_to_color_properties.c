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
 int /*<<< orphan*/  S_COLOR ; 
 int /*<<< orphan*/  S_COLOR_TEXT ; 
 int /*<<< orphan*/  S_SWITCH_POINT ; 
 int /*<<< orphan*/  S_SWITCH_POINT_TEXT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  obs_properties_add_color (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_int_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static obs_properties_t *fade_to_color_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();

	obs_properties_add_color(props, S_COLOR, S_COLOR_TEXT);
	obs_property_t *p = obs_properties_add_int_slider(
		props, S_SWITCH_POINT, S_SWITCH_POINT_TEXT, 0, 100, 1);
	obs_property_int_set_suffix(p, "%");

	UNUSED_PARAMETER(data);
	return props;
}