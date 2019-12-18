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
 int /*<<< orphan*/  S_GAIN_DB ; 
 int /*<<< orphan*/  TEXT_GAIN_DB ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/ * obs_properties_add_float_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_float_set_suffix (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static obs_properties_t *gain_properties(void *data)
{
	obs_properties_t *ppts = obs_properties_create();

	obs_property_t *p = obs_properties_add_float_slider(
		ppts, S_GAIN_DB, TEXT_GAIN_DB, -30.0, 30.0, 0.1);
	obs_property_float_set_suffix(p, " dB");

	UNUSED_PARAMETER(data);
	return ppts;
}