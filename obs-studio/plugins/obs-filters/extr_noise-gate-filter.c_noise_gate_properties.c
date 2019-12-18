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
 int /*<<< orphan*/  S_ATTACK_TIME ; 
 int /*<<< orphan*/  S_CLOSE_THRESHOLD ; 
 int /*<<< orphan*/  S_HOLD_TIME ; 
 int /*<<< orphan*/  S_OPEN_THRESHOLD ; 
 int /*<<< orphan*/  S_RELEASE_TIME ; 
 int /*<<< orphan*/  TEXT_ATTACK_TIME ; 
 int /*<<< orphan*/  TEXT_CLOSE_THRESHOLD ; 
 int /*<<< orphan*/  TEXT_HOLD_TIME ; 
 int /*<<< orphan*/  TEXT_OPEN_THRESHOLD ; 
 int /*<<< orphan*/  TEXT_RELEASE_TIME ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  VOL_MAX ; 
 int /*<<< orphan*/  VOL_MIN ; 
 int /*<<< orphan*/ * obs_properties_add_float_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * obs_properties_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_float_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static obs_properties_t *noise_gate_properties(void *data)
{
	obs_properties_t *ppts = obs_properties_create();
	obs_property_t *p;

	p = obs_properties_add_float_slider(ppts, S_CLOSE_THRESHOLD,
					    TEXT_CLOSE_THRESHOLD, VOL_MIN,
					    VOL_MAX, 1.0);
	obs_property_float_set_suffix(p, " dB");
	p = obs_properties_add_float_slider(ppts, S_OPEN_THRESHOLD,
					    TEXT_OPEN_THRESHOLD, VOL_MIN,
					    VOL_MAX, 1.0);
	obs_property_float_set_suffix(p, " dB");
	p = obs_properties_add_int(ppts, S_ATTACK_TIME, TEXT_ATTACK_TIME, 0,
				   10000, 1);
	obs_property_int_set_suffix(p, " ms");
	p = obs_properties_add_int(ppts, S_HOLD_TIME, TEXT_HOLD_TIME, 0, 10000,
				   1);
	obs_property_int_set_suffix(p, " ms");
	p = obs_properties_add_int(ppts, S_RELEASE_TIME, TEXT_RELEASE_TIME, 0,
				   10000, 1);
	obs_property_int_set_suffix(p, " ms");

	UNUSED_PARAMETER(data);
	return ppts;
}