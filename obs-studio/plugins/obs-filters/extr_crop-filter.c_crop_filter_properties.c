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
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/ * obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relative_clicked ; 

__attribute__((used)) static obs_properties_t *crop_filter_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();

	obs_property_t *p = obs_properties_add_bool(
		props, "relative", obs_module_text("Crop.Relative"));

	obs_property_set_modified_callback(p, relative_clicked);

	obs_properties_add_int(props, "left", obs_module_text("Crop.Left"),
			       -8192, 8192, 1);
	obs_properties_add_int(props, "top", obs_module_text("Crop.Top"), -8192,
			       8192, 1);
	obs_properties_add_int(props, "right", obs_module_text("Crop.Right"),
			       -8192, 8192, 1);
	obs_properties_add_int(props, "bottom", obs_module_text("Crop.Bottom"),
			       -8192, 8192, 1);
	obs_properties_add_int(props, "cx", obs_module_text("Crop.Width"), 0,
			       8192, 1);
	obs_properties_add_int(props, "cy", obs_module_text("Crop.Height"), 0,
			       8192, 1);

	UNUSED_PARAMETER(data);
	return props;
}