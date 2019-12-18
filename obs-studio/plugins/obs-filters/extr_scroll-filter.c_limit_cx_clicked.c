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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool limit_cx_clicked(obs_properties_t *props, obs_property_t *p,
			     obs_data_t *settings)
{
	bool limit_size = obs_data_get_bool(settings, "limit_cx");
	obs_property_set_visible(obs_properties_get(props, "cx"), limit_size);

	UNUSED_PARAMETER(p);
	return true;
}