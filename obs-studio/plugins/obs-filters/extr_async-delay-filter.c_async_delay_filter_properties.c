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
 int /*<<< orphan*/  SETTING_DELAY_MS ; 
 int /*<<< orphan*/  TEXT_DELAY_MS ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/ * obs_properties_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static obs_properties_t *async_delay_filter_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();

	obs_property_t *p = obs_properties_add_int(props, SETTING_DELAY_MS,
						   TEXT_DELAY_MS, 0, 20000, 1);
	obs_property_int_set_suffix(p, " ms");

	UNUSED_PARAMETER(data);
	return props;
}