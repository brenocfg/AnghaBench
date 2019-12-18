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
 int /*<<< orphan*/  SUP_MAX ; 
 int /*<<< orphan*/  SUP_MIN ; 
 int /*<<< orphan*/  S_SUPPRESS_LEVEL ; 
 int /*<<< orphan*/  TEXT_SUPPRESS_LEVEL ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/ * obs_properties_add_int_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static obs_properties_t *noise_suppress_properties(void *data)
{
	obs_properties_t *ppts = obs_properties_create();

	obs_property_t *p = obs_properties_add_int_slider(ppts,
							  S_SUPPRESS_LEVEL,
							  TEXT_SUPPRESS_LEVEL,
							  SUP_MIN, SUP_MAX, 1);
	obs_property_int_set_suffix(p, " dB");

	UNUSED_PARAMETER(data);
	return ppts;
}